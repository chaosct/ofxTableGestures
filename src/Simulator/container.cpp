/*

    ofxTableGestures (formerly OF-TangibleFramework)
    Developed for Taller de Sistemes Interactius I
    Universitat Pompeu Fabra

    Copyright (c) 2010 Daniel Gallardo Grassot <daniel.gallardo@upf.edu>

    Permission is hereby granted, free of charge, to any person
    obtaining a copy of this software and associated documentation
    files (the "Software"), to deal in the Software without
    restriction, including without limitation the rights to use,
    copy, modify, merge, publish, distribute, sublicense, and/or sell
    copies of the Software, and to permit persons to whom the
    Software is furnished to do so, subject to the following
    conditions:

    The above copyright notice and this permission notice shall be
    included in all copies or substantial portions of the Software.

    THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
    EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES
    OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
    NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT
    HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
    WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
    FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
    OTHER DEALINGS IN THE SOFTWARE.

*/

#include "container.hpp"
#include "ofUtils.h" // ofGetElapsedTimef();

#include "GenericManager.hpp"
#include "GraphicDispatcher.hpp"

#include "Polygon.hpp"
#include "Text.hpp"
#include "Line.hpp"

using namespace simulator;

// Container class ////////////////////////
Container::Container(unsigned int _sid, float _xpos, float _ypos,
                    float _xspeed, float _yspeed, float _maccel):
        sid(_sid),
        position(_xpos, _ypos),
        speed(_xspeed, _yspeed),
        maccel(_maccel),
        mouse_on(false),
        previous_coords(position),
        previous_time(ofGetElapsedTimef()),
        mspeed(0){}

Container::~Container(){
    if(graphic != NULL){
        GenericManager::get<GraphicDispatcher>()->removeGraphic(graphic);
    }
}

bool Container::Collide(float x, float y){
    return graphic->collideGraphic(ofPoint(x, y));
}

void Container::Add(float x, float y, bool only){
    previous_coords.set(x, y);
    previous_time = ofGetElapsedTimef();
}

void Container::Update(float x, float y, bool only){
    // Update position
    ofVec2f old_pos(position);
    position += ofVec2f(x, y) - previous_coords;
    previous_coords.set(x,y);

    // Update speed
    float actual_time = ofGetElapsedTimef();
    float dt = actual_time - previous_time;
    if (dt > 0.01f){
        previous_time = actual_time;
        ofVec2f delta(position - old_pos);
        speed.set(delta/dt);

        // Update acceleration
        float mspeed_old = mspeed;
        mspeed = delta.length()/dt;
        maccel = maccel/2 + (mspeed - mspeed_old) / dt; // Filtered
    }
    updateGraphic();
}

void Container::setVisible(bool v){
    graphic->setVisible(v);
}

// Cursor class ////////////////////////
simulator::Cursor::Cursor(unsigned int _sid,
                float _xpos, float _ypos,
                float _xspeed, float _yspeed,
                float _maccel):
        Container(_sid, _xpos, _ypos, _xspeed, _yspeed, _maccel),
        holded(false),
        selected(false){
    GenericManager::get<GraphicDispatcher>()->createGraphic(graphic, APP_LAYER+50);
    graphic->circle(CURSOR_RADIUS);
    ofColor color(100, 100, 100, 80);
    #ifdef ONLY_SIMULATOR
    color.a = 255;
    #endif
    graphic->setColor(color);
    updateGraphic();
}

void simulator::Cursor::updateGraphic(){
    graphic->setPosition(position);
}

void simulator::Cursor::hold(bool h){
    holded = h;
}

bool simulator::Cursor::isHolded(){
    return holded;
}

void simulator::Cursor::select(bool s){
    selected = s;
    ofColor color(100, 100, 100, 80);
    if (selected){
        color.set(50, 150, 50, 80);
    }
    #ifdef ONLY_SIMULATOR
    color.a = 255;
    #endif
    graphic->setColor(color);
}

bool simulator::Cursor::isSelected(){
    return selected;
}

// Object class ////////////////////////
Object::Object(unsigned int _sid, unsigned int _fid,
                float _xpos, float _ypos,
                float _angle, float _xspeed, float _yspeed, float _rspeed,
                float _maccel, float _raccel,
                int _trayNumber, tableGraphics::Polygon* source):
        Container(_sid, _xpos, _ypos, _xspeed, _yspeed, _maccel),
        fid(_fid),
        angle(_angle),
        rspeed(_rspeed),
        raccel(_raccel),
        tray_number(_trayNumber),
        isUp(false),
        angle_old(angle),
        previous_angle_time(ofGetElapsedTimef()),
        rspeed_old(rspeed){
    if (source != NULL){
        graphic = source;
    }else{
        GenericManager::get<GraphicDispatcher>()->createGraphic(graphic, APP_LAYER+50);
        graphic->circle(0.05f);
        graphic->setColor(ofColor(255, 255, 255, 255));
    }
    graphic->setCollide(true);

    GenericManager::get<GraphicDispatcher>()->createGraphic(idNumber, NOT_LAYER);
    idNumber->useGlobalSize(false);
    *idNumber << fid;

    GenericManager::get<GraphicDispatcher>()->createGraphic(angleLine, APP_LAYER+50);
    angleLine->setEndpoints(ofVec2f(0, 0), ofVec2f(0, OBJECT_RADIUS));
    angleLine->setColor(ofColor(255, 127, 63, 180));
    updateGraphic();
}

void Object::AddAngle(bool only){
    angle_old = angle;
    previous_angle_time = ofGetElapsedTimef();
    rspeed_old = 0;
    if (!only){
        this->Add(0,0,true);
    }
}

void Object::UpdateAngle(float _angle, bool only){
    float new_angle = ofGetElapsedTimef();
    float dta = previous_angle_time - new_angle;
    if(dta == 0) return;
    angle_old = angle;
    angle += _angle;
    if(angle >= TWO_PI)angle = angle-TWO_PI;
    if(angle < 0)angle = angle+TWO_PI;

    float da = angle-angle_old;
    if (da>(PI*1.5f)) da-=TWO_PI;
    else if (da<(PI*-1.5f)) da+=TWO_PI;

    da = da/TWO_PI;
    rspeed_old = rspeed;
    rspeed = da /dta;
    raccel = raccel/2 + (rspeed - rspeed_old)/dta; // Filtered
    if (!only){
        this->Update(0,0,true);
    }
}

void Object::Add(float x, float y,bool only){
    Container::Add(x,y,only);
    if (!only){
        AddAngle(true);
    }
}

void Object::Update(float x, float y,bool only){
    Container::Update(x,y,only);
    if (!only){
        UpdateAngle(0,true);
    }
}

void Object::updateGraphic(){
    graphic->setPosition(position, angle * 180/PI);
    angleLine->setPosition(position, angle * 180/PI);
    idNumber->setPosition(position);
}

void Object::setVisible(bool v){
    Container::setVisible(v);
    idNumber->setVisible(v);
    angleLine->setVisible(v);
}

