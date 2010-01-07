/*
* Daniel Gallardo Grassot
* dgallardo@iua.upf.edu
* Universitat Pompeu Fabra
* Music Technology Group
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
{
    LoadDistortion();
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
        ofDrawBitmapString(msg.str(), 0, 0);
        glPopMatrix();
    }
}

void TableApp::draw(){
    StartDistortion();
    grid->Draw(calibration_enabled,calibration_mode);
    Draw();
    EndDistortion();
    ///Draws Info & help
    DrawInfo();
    DrawHelp();
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

}

//--------------------------------------------------------------
void TableApp::keyReleased(int key){
    switch(key)
    {
        case 'f':
            #ifdef TARGET_WIN32
                if(!full){
                    ofBeginCustomFullscreen(0,0,2048, 768);
                }else{
                    ofEndCustomFullscreen();
                }
                full = !full;
            #else
                ofToggleFullscreen();
            #endif
		break;
		case 'c':
            if(calibration_enabled)SaveDistortion();
            calibration_enabled = !calibration_enabled;
        break;
        case OF_KEY_RETURN:
            if(calibration_enabled) calibration_mode ++;
            if(calibration_mode > 3) calibration_mode = 0;
        break;
        case OF_KEY_UP:
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
        break;
        case 'l':
            if(calibration_enabled)
                LoadDistortion();
        break;
        case 'h':
            show_help = !show_help;
        break;
        case 'd':
            distortion_enabled = !distortion_enabled;
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

}

//--------------------------------------------------------------
void TableApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void TableApp::mouseReleased(int x, int y, int button){

}


