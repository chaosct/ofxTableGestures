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

#include "Simulator.hpp"
#include <fstream>
#include "ofxGlobalConfig.hpp"
#include "ObjectFeedback.hpp"
#include "GenericManager.hpp"
#include "GraphicDispatcher.hpp"
#include "Polygon.hpp"
#include "Text.hpp"

#define INC_STEP 20

#define SCALE_FACTOR 0.91f

using namespace simulator;

Simulator::Simulator():
        sessionGenerator(1),
        fseqGenerator(0),
        hold(false),
        select(false),
        ytray(0),
        previous_timef(0),
        namepath(ofToDataPath(NAMEPATH)),
        port(DEFAULT_PORT),
        address(DEFAULT_ADDR),
        running(false){
    sender = new ofxOscSender();
    sender->setup(address,port);
    #ifndef ONLY_SIMULATOR
    loaded = LoadConfigFile(ofToDataPath(NAMEPATH));
    #endif
    objects.clear();
    loadObjects();


    GenericManager::get<GraphicDispatcher>()->createGraphic(tray, APP_LAYER-50);
    tray->setVisible(false);
    tray->addVertex(ofVec2f(1.0f, 0.0f));
    tray->addVertex(ofVec2f(1.0f, 1.0f));
    tray->addVertex(ofVec2f(0.0f, 1.0f));
    tray->addVertex(ofVec2f(0.0f, 1.1f));
    tray->addVertex(ofVec2f(1.1f, 1.1f));
    tray->addVertex(ofVec2f(1.1f, 0.0f));
    tray->setColor(ofColor(90, 100, 110));

    GenericManager::get<GraphicDispatcher>()->createGraphic(simLog, NOT_LAYER);
    simLog->setVisible(false);
    simLog->setPosition(ofVec2f(0.01f, 1.02f));
    simLog->setColor(ofColor(255, 127, 63));
    simLog->useGlobalSize(false);
}

Simulator::~Simulator(){
    //SaveFile();
    if(!loaded){
        std::ofstream ofs(namepath.c_str());
        ofs << "#Simulator config file." << std::endl;
        ofs << "#p -> port" << std::endl;
        ofs << "#a -> address" << std::endl;
        ofs << "#o -> object = fid shape red green blue alpha [shape = circle, square, star, square_rounded, pentagon, dodecahedron]" << std::endl;
        ofs << "p " << DEFAULT_PORT << std::endl;
        ofs << "a " << DEFAULT_ADDR << std::endl;
        ofs << "d" << std::endl;
    }
    delete sender;
}

void Simulator::run(bool r){
    running = r;
    if (!running){
        Reset();
    }
    tray->setVisible(running);
    simLog->setVisible(running);

    for (object_list::iterator it = objects.begin(); it != objects.end(); it++){
        (*it)->setVisible(running);
    }
}

bool Simulator::isRunning(){
    return running;
}

bool Simulator::LoadConfigFile(std::string path){
    std::ifstream infile(path.c_str());
    std::string tmp;
    char first;
    if(infile.is_open()){
        while (!infile.eof()){
            infile >> first ;
            if(first == '#'){
                //it is a coment
            }else if(first == 'p'){
                //set port
                infile >> port;
            }else if(first == 'a'){
                //set addr
                infile >> address;
            }else if(first == 'o'){
                //set object
            }
            getline(infile,tmp);
        }
        infile.close();
        return true;
    }
    return false;
}

void Simulator::SortObject(Object* o){
    float x = 1.05f;
    float y = o->tray_number * 0.1f + 0.05f;
    o->Add(o->position.x, o->position.y);
    o->Update(x, y);
}

bool Simulator::IsAtLateralTray(Container* c){
    if(c->position.x > 1){
        return true;
    }else{
        return false;
    }
}

bool Simulator::IsAtBottomTray(Container* c){
    if(c->position.y > 1){
        return true;
    }else{
        return false;
    }
}

bool Simulator::IsOnTheScene(Container* c){
    if(!IsAtLateralTray(c) && !IsAtBottomTray(c) &&
         c->position.x >= 0 && c->position.y >= 0){
        return true;
    }else{
        return false;
    }
}

void Simulator::Update(){
    float actual = ofGetElapsedTimef();
    if(actual - previous_timef > 1){
        updateCursors();
        updateObjects();
        previous_timef = actual;
    }
}

Container* Simulator::Collide(float x, float y, bool only_objects){
    //collide with objects
    for(object_list::iterator it = objects.begin(); it != objects.end(); it++){
        if((*it)->Collide(x,y)){
            (*it)->Add(x,y);
            return (*it);
        }
    }
    if(!only_objects){
        //collide with cursors
        for(cursor_list::iterator it = cursors.begin(); it != cursors.end(); it++){

            // Workaround to overcome the implicit
            //   one-cursor-can-only-collide-with-one-graphic-at-a-time invariant.
            (*it)->graphic->setCollide(true);
            if((*it)->Collide(x,y)){
                (*it)->graphic->setCollide(false);
                (*it)->Add(x,y);
                return (*it);
            }
            // In the future, maybe would be better implement some way to allow
            //   multiple graphics assignments to each cursor.
            (*it)->graphic->setCollide(false);
        }
    }
    return NULL;
}

void Simulator::mouseDragged(float x, float y, int button){
    switch(button){
    case 0:
        // Objects
        for(object_list::iterator it = objects.begin(); it != objects.end(); it++){
            if((*it)->mouse_on){
                (*it)->Update(x,y);
                if(select){
                    (*it)->isUp=true;
                    objectRemoved(*it);
                    (*it)->sid = 0;
                }
                else{
                    (*it)->isUp=false;
                    objectUpdated(*it);
                }
                return;
            }
        }

        // Cursors
        for(cursor_list::iterator it = cursors.begin(); it != cursors.end(); it++){
            if((*it)->mouse_on){
                (*it)->Update(x,y);
                cursorUpdated(*it);
                if ((*it)->isSelected()){
                    // Update all selected cursors
                    for (it = cursors.begin(); it != cursors.end(); ++it){
                        if ((*it)->isSelected()){
                            (*it)->Update(x, y);
                            cursorUpdated(*it);
                        }
                    }
                }
                break; // Cursor already found.
            }
        }
        break;

    case 2:
        #ifdef ONLY_SIMULATOR
        if(!ONLY_SIMULATOR_ENABLE_ANGLE){
	    break;
	}
        #endif
        float increment = y - previous_y;
        for(object_list::iterator it = objects.begin(); it != objects.end(); it++){
            if((*it)->mouse_on){
                (*it)->UpdateAngle(4*PI*increment);
                if(!(*it)->isUp)objectUpdated(*it);
            }
        }
        previous_y = y;
        break;
    }
}

void Simulator::mousePressed(float x, float y, int button){
    if (!running){
        return;
    }
    Container* tmp = Collide(x, y);
    simulator::Cursor* c = dynamic_cast<simulator::Cursor*>(tmp);
    Object* o = dynamic_cast<Object*>(tmp);
    switch(button){
    case 0:
        if (tmp == NULL){
            tmp = newCursor(ofVec2f(x, y));
        }
        tmp->mouse_on=true;
        if(c!=NULL && c->isSelected())
        {
            for(cursor_list::iterator it = cursors.begin(); it != cursors.end(); it++){
                if((*it)->isSelected())(*it)->Add(x,y);
            }
        }
        if(o != NULL){
            if(select){
                o->isUp=true;
                objectRemoved(o);
                o->sid = 0;
            }
            else{
                o->isUp=false;
                objectUpdated(o);
            }
        }
        break;

    case 2:
        #ifdef ONLY_SIMULATOR
        if(!ONLY_SIMULATOR_ENABLE_ANGLE){
	    break;
	}
        #endif
        if(tmp != NULL){
            previous_y = y;
            tmp->mouse_on=true;
        }
        for(object_list::iterator it = objects.begin(); it != objects.end(); it++){
            if((*it)->mouse_on){
                (*it)->AddAngle();
            }
        }
        break;

    case 3:
        MoveYTray(INC_STEP);
        for(object_list::iterator it = objects.begin(); it != objects.end(); it++){
            if((*it)->mouse_on)
                (*it)->UpdateAngle(PI/30,true);
        }
        break;

    case 4:
        MoveYTray(-INC_STEP);
        MoveYTray(INC_STEP);
        for(object_list::iterator it = objects.begin(); it != objects.end(); it++){
            if((*it)->mouse_on)
                (*it)->UpdateAngle(-PI/30,true);
        }
        break;
    }
}

void Simulator::mouseReleased(float, float, int button){
    if (!running){
        return;
    }
    std::vector<int> todelete;
    switch(button){
    case 0:
        //Unselect objects
        for(object_list::iterator it = objects.begin(); it != objects.end(); it++){
            if((*it)->mouse_on){
                (*it)->mouse_on=false;
                if(IsAtLateralTray(*it)) SortObject(*it);
                if(select){
                    (*it)->isUp=true;
                    objectRemoved(*it);
                    (*it)->sid = 0;
                }
                else{
                    (*it)->isUp=false;
                    objectUpdated(*it);
                }
            }
        }
        //Unselect cursors
        for(cursor_list::iterator it = cursors.begin(); it != cursors.end(); it++){
            if((*it)->mouse_on){
                (*it)->mouse_on=false;
                int i = it - cursors.begin();
                if(!hold && !(*it)->isHolded())todelete.push_back(i);
                if(hold && (*it)->isHolded()){
                    (*it)->hold(false);
                    todelete.push_back(i);
                }
                else (*it)->hold(true);
                if((*it)->isHolded() && select){
                    (*it)->select(!(*it)->isSelected());
                }
            }
        }
        //erase cursors
        for( std::vector<int>::iterator it = todelete.begin(); it != todelete.end(); it++ ){
            simulator::Cursor* tmp = cursors[(*it)];
            int k = *it;
            cursors.erase(cursors.begin()+k);
            cursorDeleted(tmp);
            delete(tmp);
        }
        break;

    case 2:
        #ifdef ONLY_SIMULATOR
        if(!ONLY_SIMULATOR_ENABLE_ANGLE){
	    break;
	}
        #endif
        for(object_list::iterator it = objects.begin(); it != objects.end(); it++){
            if((*it)->mouse_on)(*it)->mouse_on=false;
        }
        break;
    }
}

void Simulator::Hold(bool stat){
    if(running){
        hold = stat;
    }
}

void Simulator::Select(bool stat){
    if(running){
        select = stat;
    }
}

void Simulator::MoveYTray(int step){
    ytray+=step;

    if(ytray > 0){
        ytray=0;
        return;
    }
    float max = (objects.size()-14)* OBJECT_RADIUS*ofGetHeight()*-1;
    if(ytray < max){
        ytray=(int)max;
        return;
    }

    for(object_list::iterator it = objects.begin(); it != objects.end(); it++){
        if(IsAtLateralTray(*it)){
            (*it)->position.y += step;
        }
    }
}

void Simulator::Reset(){
    for(object_list::iterator it = objects.begin(); it != objects.end(); it++){
        SortObject(*it);
    }
    for(cursor_list::iterator it = cursors.begin(); it != cursors.end(); it++){
        cursorDeleted(*it);
        delete (*it);
    }
    cursors.clear();

    cursors_escene.clear();
    objects_escene.clear();
    updateCursors();
    updateObjects();
    simLog->clear();
}

cursor_list::iterator Simulator::IsAtCursorList(simulator::Cursor* c){
    for(cursor_list::iterator it = cursors_escene.begin(); it != cursors_escene.end(); it++){
        if((*it)->sid == c->sid) return it;
    }
    return cursors_escene.end();
}

object_list::iterator Simulator::IsAtObjectList(Object* o){
    for(object_list::iterator it = objects_escene.begin(); it != objects_escene.end(); it++){
        if((*it)->sid == o->sid) return it;
    }
    return objects_escene.end();
}

///Message generators...
void Simulator::cursorUpdated(simulator::Cursor* c){
    cursor_list::iterator it = IsAtCursorList(c);
    if(IsOnTheScene(c)){
        if(it != cursors_escene.end()){
            //update cur
            updateTuioCursor(c);
        }else{
            //add cur
            addTuioCursor(c);
            cursors_escene.push_back(c);
        }
    }else{
        if(it != cursors_escene.end()){
            //remove cur
            cursors_escene.erase(it);
            removeTuioCursor(c);
            c->sid = sessionGenerator++;
        }
    }
}

void Simulator::cursorDeleted(simulator::Cursor* c){
    cursor_list::iterator it = IsAtCursorList(c);
    if(it != cursors_escene.end()){
        //remove cur
        cursors_escene.erase(it);
        removeTuioCursor(c);
    }
}

void Simulator::objectUpdated(Object* o){
    if(o->isUp){
        objectRemoved(o);
        return;
    }

    object_list::iterator it = IsAtObjectList(o);
    if(IsOnTheScene(o)){
        if(it != objects_escene.end()){
            //update obj
            updateTuioObject(o);
        }else{
            //add obj
            o->sid= sessionGenerator++;
            addTuioObject(o);
            objects_escene.push_back(o);
        }
    }else{
        if(it != objects_escene.end()){
            //remove obj
            objects_escene.erase(it);
            removeTuioObject(o);
            o->sid = 0;
        }
    }

}

void Simulator::objectRemoved(Object* o){
    object_list::iterator it = IsAtObjectList(o);
    if(it != objects_escene.end()){
        //remove obj
        objects_escene.erase(it);
        removeTuioObject(o);
        o->sid = 0;
    }
}

void Simulator::addTuioObject(Object* o){
    ofxOscBundle Bundle;
    //alive message
    ofxOscMessage message_alive;
    message_alive.setAddress("/tuio/2Dobj");
    message_alive.addStringArg("alive");
    for(object_list::iterator it = objects_escene.begin(); it != objects_escene.end(); it++){
        message_alive.addIntArg((*it)->sid);
    }
    //set message
    ofxOscMessage message_set;
    message_set.setAddress("/tuio/2Dobj");
    message_set.addStringArg("set");
    message_set.addIntArg(o->sid);
    message_set.addIntArg(o->fid);
    message_set.addFloatArg(o->position.x);
    message_set.addFloatArg(o->position.y);
    message_set.addFloatArg(o->angle);
    message_set.addFloatArg(o->speed.x);
    message_set.addFloatArg(o->speed.y);
    message_set.addFloatArg(o->rspeed);
    message_set.addFloatArg(o->maccel);
    message_set.addFloatArg(o->raccel);
    //fseq message
    fseqGenerator++;
    ofxOscMessage message_frame;
    message_frame.setAddress("/tuio/2Dobj");
    message_frame.addStringArg("fseq");
    message_frame.addIntArg(fseqGenerator);
    //build bundle
    Bundle.addMessage(message_alive);
    Bundle.addMessage(message_set);
    Bundle.addMessage(message_frame);
    sender->sendBundle(Bundle);
    stringstream ostring;
    ostring.precision(3);
    ostring.setf(std::ios::fixed, std::ios::floatfield);
    ostring <<
            "add /tuio/2Dobj SID: " << o->sid <<
            ", FID: " << o->fid <<
            ", X: " << o->position.x <<
            ", Y: " << o->position.y <<
            ", angle: " << o->angle <<
            ", xspeed: " << o->speed.x <<
            ", yspeed: " << o->speed.y <<
            ", rspeed: " << o->rspeed <<
            ", maccel: " << o->maccel <<
            ", raccel: " << o->raccel;
    pushMessage(ostring.str());
}

void Simulator::updateTuioObject(Object* o){
    ofxOscBundle Bundle;
    //alive message
    ofxOscMessage message_alive;
    message_alive.setAddress("/tuio/2Dobj");
    message_alive.addStringArg("alive");
    for(object_list::iterator it = objects_escene.begin(); it != objects_escene.end(); it++){
        message_alive.addIntArg((*it)->sid);
    }
    //set message
    ofxOscMessage message_set;
    message_set.setAddress("/tuio/2Dobj");
    message_set.addStringArg("set");
    message_set.addIntArg(o->sid);
    message_set.addIntArg(o->fid);
    message_set.addFloatArg(o->position.x);
    message_set.addFloatArg(o->position.y);
    message_set.addFloatArg(o->angle);
    message_set.addFloatArg(o->speed.x);
    message_set.addFloatArg(o->speed.y);
    message_set.addFloatArg(o->rspeed);
    message_set.addFloatArg(o->maccel);
    message_set.addFloatArg(o->raccel);
    //fseq message
    fseqGenerator++;
    ofxOscMessage message_frame;
    message_frame.setAddress("/tuio/2Dobj");
    message_frame.addStringArg("fseq");
    message_frame.addIntArg(fseqGenerator);
    //build bundle
    Bundle.addMessage(message_alive);
    Bundle.addMessage(message_set);
    Bundle.addMessage(message_frame);
    sender->sendBundle(Bundle);
    stringstream ostring;
    ostring.precision(3);
    ostring.setf(std::ios::fixed, std::ios::floatfield);
    ostring <<
            "update /tuio/2Dobj SID: " << o->sid <<
            ", FID: " << o->fid <<
            ", X: " << o->position.x <<
            ", Y: " << o->position.y <<
            ", angle: " << o->angle <<
            ", xspeed: " << o->speed.x <<
            ", yspeed: " << o->speed.y <<
            ", rspeed: " << o->rspeed <<
            ", maccel: " << o->maccel <<
            ", raccel: " << o->raccel;
    pushMessage(ostring.str());
}

void Simulator::removeTuioObject(Object* o){
    ofxOscBundle Bundle;
    ofxOscMessage message_alive;
    message_alive.setAddress("/tuio/2Dobj");
    message_alive.addStringArg("alive");
    for(object_list::iterator it = objects_escene.begin(); it != objects_escene.end(); it++){
        message_alive.addIntArg((*it)->sid);
    }
    fseqGenerator++;
    ofxOscMessage message_frame;
    message_frame.setAddress("/tuio/2Dobj");
    message_frame.addStringArg("fseq");
    message_frame.addIntArg(fseqGenerator);
    Bundle.addMessage(message_alive);
    Bundle.addMessage(message_frame);
    sender->sendBundle(Bundle);
    stringstream ostring;
    ostring.precision(3);
    ostring.setf(std::ios::fixed, std::ios::floatfield);
    ostring <<
            "remove /tuio/2Dobj SID: " << o->sid <<
            ", FID: " << o->fid;
    pushMessage(ostring.str());
}

void Simulator::addTuioCursor(simulator::Cursor* c){
    ofxOscBundle Bundle;
    //alive message
    ofxOscMessage message_alive;
    message_alive.setAddress("/tuio/2Dcur");
    message_alive.addStringArg("alive");
    for(cursor_list::iterator it = cursors_escene.begin(); it != cursors_escene.end(); it++){
        message_alive.addIntArg((*it)->sid);
    }
    //set message
    ofxOscMessage message_set;
    message_set.setAddress("/tuio/2Dcur");
    message_set.addStringArg("set");
    message_set.addIntArg(c->sid);
    message_set.addFloatArg(c->position.x);
    message_set.addFloatArg(c->position.y);
    message_set.addFloatArg(c->speed.x);
    message_set.addFloatArg(c->speed.y);
    message_set.addFloatArg(c->maccel);
    //fseq message
    fseqGenerator++;
    ofxOscMessage message_frame;
    message_frame.setAddress("/tuio/2Dcur");
    message_frame.addStringArg("fseq");
    message_frame.addIntArg(fseqGenerator);
    //build bundle
    Bundle.addMessage(message_alive);
    Bundle.addMessage(message_set);
    Bundle.addMessage(message_frame);
    sender->sendBundle(Bundle);
    stringstream ostring;
    ostring.precision(3);
    ostring.setf(std::ios::fixed, std::ios::floatfield);
    ostring <<
            "add /tuio/2Dcur SID: " << c->sid <<
            ", X: " << c->position.x <<
            ", Y: " << c->position.y <<
            ", xspeed: " << c->speed.x <<
            ", yspeed: " << c->speed.y <<
            ", maccel: " << c->maccel;
    pushMessage(ostring.str());
}

void Simulator::updateTuioCursor(simulator::Cursor* c){
    ofxOscBundle Bundle;
    //alive message
    ofxOscMessage message_alive;
    message_alive.setAddress("/tuio/2Dcur");
    message_alive.addStringArg("alive");
    for(cursor_list::iterator it = cursors_escene.begin(); it != cursors_escene.end(); it++){
        message_alive.addIntArg((*it)->sid);
    }
    //set message
    ofxOscMessage message_set;
    message_set.setAddress("/tuio/2Dcur");
    message_set.addStringArg("set");
    message_set.addIntArg(c->sid);
    message_set.addFloatArg(c->position.x);
    message_set.addFloatArg(c->position.y);
    message_set.addFloatArg(c->speed.x);
    message_set.addFloatArg(c->speed.y);
    message_set.addFloatArg(c->maccel);
    //fseq message
    fseqGenerator++;
    ofxOscMessage message_frame;
    message_frame.setAddress("/tuio/2Dcur");
    message_frame.addStringArg("fseq");
    message_frame.addIntArg(fseqGenerator);
    //build bundle
    Bundle.addMessage(message_alive);
    Bundle.addMessage(message_set);
    Bundle.addMessage(message_frame);
    sender->sendBundle(Bundle);
    stringstream ostring;
    ostring.precision(3);
    ostring.setf(std::ios::fixed, std::ios::floatfield);
    ostring <<
            "update /tuio/2Dcur SID: " << c->sid <<
            ", X: " << c->position.x <<
            ", Y: " << c->position.y <<
            ", xspeed: " << c->speed.x <<
            ", yspeed: " << c->speed.y <<
            ", maccel: " << c->maccel;
    pushMessage(ostring.str());
}

void Simulator::removeTuioCursor(simulator::Cursor* c){
    ofxOscBundle Bundle;
    ofxOscMessage message_alive;
    message_alive.setAddress("/tuio/2Dcur");
    message_alive.addStringArg("alive");
    for(cursor_list::iterator it = cursors_escene.begin(); it != cursors_escene.end(); it++){
        message_alive.addIntArg((*it)->sid);
    }
    fseqGenerator++;
    ofxOscMessage message_frame;
    message_frame.setAddress("/tuio/2Dcur");
    message_frame.addStringArg("fseq");
    message_frame.addIntArg(fseqGenerator);
    Bundle.addMessage(message_alive);
    Bundle.addMessage(message_frame);
    sender->sendBundle(Bundle);
    stringstream ostring;
    ostring.precision(3);
    ostring.setf(std::ios::fixed, std::ios::floatfield);
    ostring <<
            "remove /tuio/2Dcur SID: " << c->sid;
    pushMessage(ostring.str());
}

///missatge cada segon?
void Simulator::updateCursors(){
    //if(cursors_escene.size() == 0) return;
    ofxOscBundle Bundle;
    //alive message
    ofxOscMessage message_alive;
    message_alive.setAddress("/tuio/2Dcur");
    message_alive.addStringArg("alive");
    for(cursor_list::iterator it = cursors_escene.begin(); it != cursors_escene.end(); it++){
        message_alive.addIntArg((*it)->sid);
    }
    //fseq message
    fseqGenerator++;
    ofxOscMessage message_frame;
    message_frame.setAddress("/tuio/2Dcur");
    message_frame.addStringArg("fseq");
    message_frame.addIntArg(fseqGenerator);
    //build bundle
    Bundle.addMessage(message_alive);
    //set messages
    for(cursor_list::iterator it = cursors_escene.begin(); it != cursors_escene.end(); it++){
        ofxOscMessage message_set;
        message_set.setAddress("/tuio/2Dcur");
        message_set.addStringArg("set");
        message_set.addIntArg((*it)->sid);
        message_set.addFloatArg((*it)->position.x);
        message_set.addFloatArg((*it)->position.y);
        message_set.addFloatArg((*it)->speed.x);
        message_set.addFloatArg((*it)->speed.y);
        message_set.addFloatArg((*it)->maccel);
        Bundle.addMessage(message_set);
    }
    Bundle.addMessage(message_frame);
    sender->sendBundle(Bundle);
}

void Simulator::updateObjects(){
    //if(objects_escene.size() == 0) return;
    ofxOscBundle Bundle;
    //alive message
    ofxOscMessage message_alive;
    message_alive.setAddress("/tuio/2Dobj");
    message_alive.addStringArg("alive");
    for(object_list::iterator it = objects_escene.begin(); it != objects_escene.end(); it++){
        message_alive.addIntArg((*it)->sid);
    }
    //fseq message
    fseqGenerator++;
    ofxOscMessage message_frame;
    message_frame.setAddress("/tuio/2Dobj");
    message_frame.addStringArg("fseq");
    message_frame.addIntArg(fseqGenerator);
    //build bundle
    Bundle.addMessage(message_alive);
    //set message
    for(object_list::iterator it = objects_escene.begin(); it != objects_escene.end(); it++){
        ofxOscMessage message_set;
        message_set.setAddress("/tuio/2Dobj");
        message_set.addStringArg("set");
        message_set.addIntArg((*it)->sid);
        message_set.addIntArg((*it)->fid);
        message_set.addFloatArg((*it)->position.x);
        message_set.addFloatArg((*it)->position.y);
        message_set.addFloatArg((*it)->angle);
        message_set.addFloatArg((*it)->speed.x);
        message_set.addFloatArg((*it)->speed.y);
        message_set.addFloatArg((*it)->rspeed);
        message_set.addFloatArg((*it)->maccel);
        message_set.addFloatArg((*it)->raccel);
        Bundle.addMessage(message_set);
    }
    Bundle.addMessage(message_frame);
    sender->sendBundle(Bundle);
}

void Simulator::pushMessage(string message){
    if(notify.size() >= 5)
        notify.pop_back();
    notify.push_front(message);
    simLog->clear();
    for (std::list<string>::iterator it = notify.begin(); it != notify.end(); it++){
        *simLog << *it << std::endl;;
    }
}

void Simulator::loadObjects(){
    int objnum = 10;
    #ifdef ONLY_SIMULATOR
    objnum = ONLY_SIMULATOR_NOBJECTS;
    #endif
    for (int fid = 0; fid < objnum; ++fid){
        tableGraphics::Polygon* objGraphic;
        GenericManager::get<GraphicDispatcher>()->createGraphic(objGraphic);
        GenericManager::get<ObjectFeedback>()->setGraphic(fid, objGraphic);
        ofColor color(objGraphic->getColor());
        color.a = 100;
        objGraphic->setColor(color);
        objGraphic->setStrokeColor(color);

        // Create new Object instance
        Object* newObj = new Object(0, fid, 0, 0, 0, 0, 0, 0, 0, 0, fid, objGraphic);
        newObj->setVisible(false);
        SortObject(newObj);
        objects.push_back(newObj);
    }
}

simulator::Cursor* Simulator::newCursor(ofVec2f initPos){
    simulator::Cursor* new_cursor = new simulator::Cursor(sessionGenerator++, initPos.x, initPos.y, 0, 0, 0);
    cursors.push_back(new_cursor);
    cursorUpdated(new_cursor);
    return new_cursor;
}

