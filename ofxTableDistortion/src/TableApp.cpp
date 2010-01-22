/*
* Daniel Gallardo Grassot
* daniel.gallardo@upf.edu
* Universitat Pompeu Fabra
* Music Technology Group
*/
/*

    TSIframework . Framework for Taller de Sistemes Interactius I
    Universitat Pompeu Fabra

    Copyright (c) 2009 Daniel Gallardo Grassot <daniel.gallardo@upf.edu>

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

#define WIDTH_STEP 0.005
#define ANGLE_STEP 1
#define DISTORTION_PATH "calibration.conf"

TableApp::TableApp():
    calibration_enabled(false),
    calibration_mode(0),
    show_help(false),
    show_info(false),
    distortion_enabled(false),
    height_offset(1),
    width_offset(1),
    center_x(0),
    center_y(0),
    angle_h(0),
    angle_w(0),
    angle(0),
    DistortionPath(DISTORTION_PATH),
    hide_cursor(true)
    #ifdef SIMULATOR
    ,simulator(new simulator::Simulator()),
    is_simulating(false)
    #endif
{
    LoadDistortion();
}

TableApp::~TableApp(){
    #ifdef SIMULATOR
    delete simulator;
    #endif
    delete grid;
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
    ofSetWindowTitle("Table APP    press 'h' to show help content");
    Setup();
    ofBackground(0, 0, 0);
    ofHideCursor();
}

//--------------------------------------------------------------
void TableApp::update(){
    //float framerate = ofGetFrameRate();
    //std::cout << "FPS: " << framerate << std::endl;
    Update();
}

//--------------------------------------------------------------

void TableApp::SaveDistortion()
{
    std::ofstream ofs(DistortionPath.c_str());
    ofs << "#Calibration File for the tabletop framewok" << std::endl;
    ofs << "#" << std::endl;
    ofs << "# Distortion Enabled:" << std::endl;
    ofs << distortion_enabled << std::endl;
    ofs << "# X_offset:" << std::endl;
    ofs << center_x << std::endl;
    ofs << "# y_offset:" << std::endl;
    ofs << center_y << std::endl;
    ofs << "# height_offset:" << std::endl;
    ofs << height_offset << std::endl;
    ofs << "# width_offset:" << std::endl;
    ofs << width_offset << std::endl;
    ofs << "# angle:" << std::endl;
    ofs << angle << std::endl;
    ofs << "# angle_h:" << std::endl;
    ofs << angle_h << std::endl;
    ofs << "# angle_w:" << std::endl;
    ofs << angle_w << std::endl;
}

void TableApp::LoadDistortion()
{
    std::ifstream infile(DistortionPath.c_str());
    std::string tmp ("st");
    if(infile.is_open())
    {
        getline(infile,tmp);
        getline(infile,tmp);
        getline(infile,tmp);
        infile >> distortion_enabled;
        getline(infile,tmp);getline(infile,tmp);
        infile >> center_x;
        getline(infile,tmp);getline(infile,tmp);
        infile >> center_y;
        getline(infile,tmp);getline(infile,tmp);
        infile >> height_offset;
        getline(infile,tmp);getline(infile,tmp);
        infile >> width_offset;
        getline(infile,tmp);getline(infile,tmp);
        infile >> angle;
        getline(infile,tmp);getline(infile,tmp);
        infile >> angle_h;
        getline(infile,tmp);getline(infile,tmp);
        infile >> angle_w;
    }
}

void TableApp::DrawInfo()
{
    if(show_info)
    {
        glPushMatrix();
        glTranslatef(50.0f,50.0f,0.0f);
        ofSetColor(0x00FF00);
        std::stringstream msg;
        msg << ofGetWidth() << "X" << ofGetHeight() << "@" <<  (int)ofGetFrameRate() << "fps" << std::endl;
        if(distortion_enabled)
            msg << "Distortion enabled" << std::endl;
        else
            msg << "Distortion disabled" << std::endl;
        msg << "Calibration data:" << std::endl;
        msg << "  x_position: " << center_x << std::endl;
        msg << "  y_position: " << center_y << std::endl;
        msg << "  height_offset: " << height_offset << std::endl;
        msg << "  width_offset: " << width_offset << std::endl;
        msg << "  angle: " << angle << std::endl;
        msg << "  angle_h: " << angle_h << std::endl;
        msg << "  angle_w: " << angle_w << std::endl;

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
    StartDistortion();
    grid->Draw(calibration_enabled,calibration_mode);
    Draw();
    EndDistortion();
    ///Draws Info & help
    DrawInfo();
    DrawHelp();
    ofPopMatrix();
    #ifdef SIMULATOR
    if(is_simulating) simulator->Draw();
    #endif
}

void TableApp::StartDistortion()
{
    if(distortion_enabled)
    {
        glPushMatrix();

        glTranslatef((ofGetWidth())/2,(ofGetHeight())/2,0);
        glRotated(angle_h,1,0,0);
        glRotated(angle_w,0,1,0);
        glRotated(angle,0,0,1);
        glScaled(width_offset,height_offset,1);
        glTranslatef(-(ofGetWidth())/2,-(ofGetHeight())/2,0);

        glTranslated(center_x,center_y,0);
    }
}

void TableApp::EndDistortion()
{
    glPopMatrix();
}
//--------------------------------------------------------------
void TableApp::keyPressed(int key){
    #ifdef SIMULATOR
    switch(key)
    {
        case 'a':
            simulator->Hold(true);
        break;
        case 'z':
            simulator->Select(true);
        break;
    }
    #endif
}

//--------------------------------------------------------------
void TableApp::keyReleased(int key){
    switch(key)
    {
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
            if(calibration_enabled)SaveDistortion();
            calibration_enabled = !calibration_enabled;
        break;
        case OF_KEY_RETURN:
            #ifdef SIMULATOR
            if(!is_simulating)
            #endif
            if(calibration_enabled) calibration_mode ++;
            if(calibration_mode > 3) calibration_mode = 0;
        break;
        case OF_KEY_UP:
            #ifdef SIMULATOR
            if(!is_simulating)
            #endif
            if(calibration_enabled)
            {
                switch(calibration_mode)
                {
                    case 0:center_y--;break;
                    case 1:height_offset+=WIDTH_STEP;break;
                    case 2:angle+=ANGLE_STEP;break;
                    case 3:angle_h+=ANGLE_STEP;break;
                }
            }
        break;
        case OF_KEY_DOWN:
            #ifdef SIMULATOR
            if(!is_simulating)
            #endif
            if(calibration_enabled)
            {
                switch(calibration_mode)
                {
                    case 0:center_y++;break;
                    case 1:height_offset-=WIDTH_STEP;break;
                    case 2:angle-=ANGLE_STEP;break;
                    case 3:angle_h-=ANGLE_STEP;break;
                }
            }
        break;
        case OF_KEY_RIGHT:
            #ifdef SIMULATOR
            if(!is_simulating)
            #endif
            if(calibration_enabled)
            {
                switch(calibration_mode)
                {
                    case 0:center_x++;break;
                    case 1:width_offset+=WIDTH_STEP;break;
                    case 2:angle+=ANGLE_STEP;break;
                    case 3:angle_w+=ANGLE_STEP;break;
                }
            }
        break;
        case OF_KEY_LEFT:
            #ifdef SIMULATOR
            if(!is_simulating)
            #endif
            if(calibration_enabled)
            {
                switch(calibration_mode)
                {
                    case 0:center_x--;break;
                    case 1:width_offset-=WIDTH_STEP;break;
                    case 2:angle-=ANGLE_STEP;break;
                    case 3:angle_w-=ANGLE_STEP;break;
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
            if(calibration_enabled)
            {
                height_offset=1;
                width_offset=1;
                center_x=0;
                center_y=0;
                angle_h=0;
                angle_w=0;
                angle=0;
            }
            #ifdef SIMULATOR
                if(is_simulating)
                    simulator->Reset();
            #endif
        break;
        case 'l':
            #ifdef SIMULATOR
            if(!is_simulating)
            #endif
            if(calibration_enabled)
                LoadDistortion();
        break;
        case 'h':
            show_help = !show_help;
        break;
        case 'd':
            #ifdef SIMULATOR
            if(!is_simulating)
            #endif
            distortion_enabled = !distortion_enabled;
        break;
        case 's':
            #ifdef SIMULATOR
                if(is_simulating){
                    ///restore distorsion
                    ///restore cursor
                    distortion_enabled = was_distorsion_enabled;
                    if(was_cursor_hide){
                        hide_cursor=true;
                        ofHideCursor();
                    }
                    is_simulating=false;
                    simulator->Reset();
                }
                else{
                    was_distorsion_enabled = distortion_enabled;
                    was_cursor_hide = hide_cursor;
                    distortion_enabled = false;
                    hide_cursor=false;
                    ofShowCursor();
                    is_simulating=true;
                }
            #endif
        break;
    }
}

//--------------------------------------------------------------
void TableApp::windowResized(int w, int h){
    grid->Resize();
}

///################################################################
/// TODO
///En un futur, implementar una espècie de tuioSimulator embeded...
///################################################################
//--------------------------------------------------------------
void TableApp::mouseMoved(int x, int y ){
}

//--------------------------------------------------------------
void TableApp::mouseDragged(int x, int y, int button){
    #ifdef SIMULATOR
    if(is_simulating) simulator->mouseDragged(x,y,button);
    #endif
}

//--------------------------------------------------------------
void TableApp::mousePressed(int x, int y, int button){
    #ifdef SIMULATOR
    if(is_simulating) simulator->mousePressed(x,y,button);
    #endif
}

//--------------------------------------------------------------
void TableApp::mouseReleased(int x, int y, int button){
    #ifdef SIMULATOR
    if(is_simulating) simulator->mouseReleased(x,y,button);
    #endif
}


