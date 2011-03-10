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

#include <fstream>
#include "TableApp.hpp"
#include "GraphicDispatcher.hpp"
#include "Renderer_plane.hpp"
#include "Renderer_to_texture.hpp"
#include "GlobalConfig.hpp"

#define WIDTH_STEP 0.005
#define ANGLE_STEP 1
#define DISTORTION_PATH "calibration.conf"

double * TableApp::calibration_matrix = NULL;

TableApp::TableApp():
//    calibration_enabled(false),
    calibration_mode(0),
    show_help(false),
    show_info(false),
    hide_cursor(true),
    #ifdef SIMULATOR
    simulator(new simulator::Simulator()),
    is_simulating(false),
    #endif
    squaredInterface(GlobalConfig::getRef("GLOBAL:SQUAREDINTERFACE",1))
{
    if(GlobalConfig::getRef("GLOBAL:RENDERTOTEXTURE",0)) renderer = new Renderer_to_texture();
    else renderer = new Renderer_plane();

    renderer->LoadDistortion();
    show_grid = false;

    ofAddListener(ofEvents.update,this,&TableApp::update);
    ofAddListener(ofEvents.keyPressed,this,&TableApp::keyPressed);
    ofAddListener(ofEvents.keyReleased,this,&TableApp::keyReleased);
    ofAddListener(ofEvents.mouseDragged,this,&TableApp::mouseDragged);
    ofAddListener(ofEvents.mousePressed,this,&TableApp::mousePressed);
    ofAddListener(ofEvents.mouseReleased,this,&TableApp::mouseReleased);
    ofAddListener(ofEvents.windowResized,this,&TableApp::windowResized);
}

TableApp::~TableApp(){
    #ifdef SIMULATOR
    delete simulator;
    #endif
    delete renderer;
    delete grid;

    ofRemoveListener(ofEvents.update,this,&TableApp::update);
    ofRemoveListener(ofEvents.keyPressed,this,&TableApp::keyPressed);
    ofRemoveListener(ofEvents.keyReleased,this,&TableApp::keyReleased);
    ofRemoveListener(ofEvents.mouseDragged,this,&TableApp::mouseDragged);
    ofRemoveListener(ofEvents.mousePressed,this,&TableApp::mousePressed);
    ofRemoveListener(ofEvents.mouseReleased,this,&TableApp::mouseReleased);
    ofRemoveListener(ofEvents.windowResized,this,&TableApp::windowResized);

}


int TableApp::GetSquareSide(){
    if(ofGetWidth() > ofGetHeight())return ofGetHeight();
    else return ofGetWidth();
}

//--------------------------------------------------------------
void TableApp::setup(){
    grid = new Grid(6,6);
    full=false;
    ofSetFrameRate(60);
    ///starts the tuioinput thread
    //tuio::tuioinput::Instance().init();
    ofSetWindowTitle("Table APP    press 'h' to show help content");
    ofBackground(0, 0, 0);
    ofHideCursor();
}

//--------------------------------------------------------------
void TableApp::update(ofEventArgs & args){
    TableApp::calibration_matrix = renderer->GetDistortionMatrix();
    ///Update input events, it says to all input gestures to process the gesture stack.
    //tuio::tuioAreaDelivery::Instance().processTevents();
    ///Update graphic data, with this command all update methods from all 'Graphics' are launched
    GraphicDispatcher::Instance().Update();
    ///Update simulator objects
    #ifdef SIMULATOR
    if(is_simulating) simulator->Update();
    #endif
}

//--------------------------------------------------------------

void TableApp::DrawInfo()
{
    if(show_info)
    {
        glPushMatrix();
        glTranslatef(50.0f,50.0f,0.0f);
        ofSetColor(0x00FF00);
        std::stringstream msg;
        msg << ofGetWidth() << "X" << ofGetHeight() << "@" <<  (int)ofGetFrameRate() << "fps" << std::endl;
        if(renderer->IsEnabled())
            msg << "Distortion enabled" << std::endl;
        else
            msg << "Distortion disabled" << std::endl;
        msg << "Calibration data:" << std::endl;
        msg << renderer->ToString();
        ofDrawBitmapString(msg.str(), 0, 0);
        glPopMatrix();
    }
}

void TableApp::DrawHelp()
{
    if(show_help)
    {
        glPushMatrix();
        glTranslatef(50.0f,200.0f,0.0f);
        ofSetColor(0x00FF00);
        std::stringstream msg;
        msg << "h - help content." << std::endl;
        msg << "i - shows graphic information content." << std::endl;
        msg << "f - toggle fullscreen." << std::endl;
        msg << "m - shows/hides cursor pointer." << std::endl;
        msg << "d - enable/disable distortion." << std::endl;
        msg << "c - calibration mode." << std::endl;
        msg << "Under calibration mode:" << std::endl;
        msg << "  r - reset calibration values." << std::endl;
        msg << "  l - load calibration file." << std::endl;
        msg << "  return  - toggle calibration parameter." << std::endl;
        msg << "  cursors - Changes the selected parameter." << std::endl;
        #ifdef SIMULATOR
        msg << "s - enable simulator." << std::endl;
        msg << "Under simulator mode:" << std::endl;
        msg << "  r - reset." << std::endl;
        msg << "  a - hold." << std::endl;
        msg << "  z - select." << std::endl;
        #endif
        ofDrawBitmapString(msg.str(), 0, 0);
        glPopMatrix();
    }
}

void TableApp::draw(){
    ofPushMatrix();
    #ifdef SIMULATOR
    if(is_simulating) ofScale(0.91f,0.91f,1.0f);
    #endif

    renderer->Start();
    ofPushMatrix();
    int shortside = min(ofGetWidth(),ofGetHeight());
    if(squaredInterface)
    {
        //if the surface is squared we center the drawing  plane
        glTranslatef((ofGetWidth()-shortside)/2.0,(ofGetHeight()-shortside)/2.0,0);
        GlobalConfig::Instance().height = 1;
        GlobalConfig::Instance().width = 1;
    }
    else
    {
        GlobalConfig::Instance().height = float(ofGetHeight())/float(shortside);
        GlobalConfig::Instance().width = float(ofGetWidth())/float(shortside);
    }
    glScalef(shortside,shortside,1);

    ///Draws all 'Graphics'
    glDisable(GL_DEPTH_TEST);
    ofPushMatrix();
    GraphicDispatcher::Instance().Draw();
    ofPopMatrix();
    glEnable(GL_DEPTH_TEST);

    ofPopMatrix();
    grid->Draw(show_grid,calibration_mode);
    renderer->End();
    ///Draws Info & help
    DrawInfo();
    DrawHelp();
    ofPopMatrix();
    #ifdef SIMULATOR
    if(is_simulating) simulator->Draw();
    #endif
}

//--------------------------------------------------------------
void TableApp::keyPressed(ofKeyEventArgs & event){
    int key = event.key;
    #ifdef SIMULATOR
    switch(key)
    {
        case 'a':
            simulator->Hold(true);
        break;
        case 'z':
            simulator->Select(true);
        break;
        default:
            KeyPressed(key);
        break;
    }
    #endif
}

//--------------------------------------------------------------
void TableApp::keyReleased(ofKeyEventArgs & event){
    int key = event.key;
    switch(key)
    {
        default:
            KeyReleased(key);
        break;
        #ifdef SIMULATOR
        case 'a':
            simulator->Hold(false);
        break;
        case 'z':
            simulator->Select(false);
        break;
        #endif
        case 'f':
            ofToggleFullscreen();
		break;
		case 'c':
            if(renderer->IsEnabled()){
                renderer->SaveDistortion();
            }
            show_grid = !show_grid;
        break;
        case OF_KEY_RETURN:
            #ifdef SIMULATOR
            if(!is_simulating)
            #endif
            if(renderer->IsEnabled() && show_grid) calibration_mode ++;
            if(calibration_mode > 3) calibration_mode = 0;
        break;
        case OF_KEY_UP:
            #ifdef SIMULATOR
            if(!is_simulating)
            #endif
            if(renderer->IsEnabled() && show_grid)
            {
                switch(calibration_mode)
                {
                    case 0:renderer->center_y--;break;
                    case 1:renderer->height_offset+=WIDTH_STEP;break;
                    case 2:renderer->angle+=ANGLE_STEP;break;
                    case 3:renderer->angle_h+=ANGLE_STEP;break;
                }
            }
        break;
        case OF_KEY_DOWN:
            #ifdef SIMULATOR
            if(!is_simulating)
            #endif
            if(renderer->IsEnabled() && show_grid)
            {
                switch(calibration_mode)
                {
                    case 0:renderer->center_y++;break;
                    case 1:renderer->height_offset-=WIDTH_STEP;break;
                    case 2:renderer->angle-=ANGLE_STEP;break;
                    case 3:renderer->angle_h-=ANGLE_STEP;break;
                }
            }
        break;
        case OF_KEY_RIGHT:
            #ifdef SIMULATOR
            if(!is_simulating)
            #endif
            if(renderer->IsEnabled() && show_grid)
            {
                switch(calibration_mode)
                {
                    case 0:renderer->center_x++;break;
                    case 1:renderer->width_offset+=WIDTH_STEP;break;
                    case 2:renderer->angle+=ANGLE_STEP;break;
                    case 3:renderer->angle_w+=ANGLE_STEP;break;
                }
            }
        break;
        case OF_KEY_LEFT:
            #ifdef SIMULATOR
            if(!is_simulating)
            #endif
            if(renderer->IsEnabled() && show_grid)
            {
                switch(calibration_mode)
                {
                    case 0:renderer->center_x--;break;
                    case 1:renderer->width_offset-=WIDTH_STEP;break;
                    case 2:renderer->angle-=ANGLE_STEP;break;
                    case 3:renderer->angle_w-=ANGLE_STEP;break;
                }
            }
        break;
        case 'i':
            show_info = !show_info;
        break;
        case 'm':
            if(hide_cursor)
            {
                hide_cursor=false;
                ofShowCursor();
            }else{
                hide_cursor=true;
                ofHideCursor();
            }
        break;
        case 'r':
            if(renderer->IsEnabled() && show_grid)
                renderer->LoadDefaultValues();
            #ifdef SIMULATOR
                if(is_simulating)
                    simulator->Reset();
            #endif
        break;
        case 'l':
            #ifdef SIMULATOR
            if(!is_simulating)
            #endif
            if(renderer->IsEnabled() && show_grid)
                renderer->LoadDistortion();
        break;
        case 'h':
            show_help = !show_help;
        break;
        case 'd':
            #ifdef SIMULATOR
            if(!is_simulating)
            {
            #endif
            if(renderer->IsEnabled()) renderer->Disable();
            else renderer->Enable();
            #ifdef SIMULATOR
            }
            #endif
        break;
        case 's':
            #ifdef SIMULATOR
                if(is_simulating){
                    ///restore distorsion
                    ///restore cursor
                    if(was_distorsion_enabled) renderer->Enable();
                    else renderer->Disable();
                    if(was_cursor_hide){
                        hide_cursor=true;
                        ofHideCursor();
                    }
                    is_simulating=false;
                    simulator->Reset();
                }
                else{
                    was_distorsion_enabled = renderer->IsEnabled();
                    was_cursor_hide = hide_cursor;
                    renderer->Disable();
                    hide_cursor=false;
                    ofShowCursor();
                    is_simulating=true;
                }
            #endif
        break;
    }
}

//--------------------------------------------------------------
void TableApp::windowResized(ofResizeEventArgs & event){
    int w = event.width;
    int h = event.height;
    #ifdef SIMULATOR
    if(is_simulating) simulator->windowResized(w,h);
    #endif
    grid->Resize();
    ///calls resize method of all 'Graphics' when nedded.
    GraphicDispatcher::Instance().Resize(w,h);
}


//--------------------------------------------------------------
void TableApp::mouseDragged(ofMouseEventArgs & event){
    #ifdef SIMULATOR
    if(is_simulating) simulator->mouseDragged(event.x,event.y,event.button);
    #endif
}

//--------------------------------------------------------------
void TableApp::mousePressed(ofMouseEventArgs & event){
    #ifdef SIMULATOR
    if(is_simulating) simulator->mousePressed(event.x,event.y,event.button);
    #endif
}

//--------------------------------------------------------------
void TableApp::mouseReleased(ofMouseEventArgs & event){
    #ifdef SIMULATOR
    if(is_simulating) simulator->mouseReleased(event.x,event.y,event.button);
    #endif
}


