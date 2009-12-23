#include "testApp.h"
#include "TEvent.h"



//--------------------------------------------------------------
void testApp::setup(){
ofSetCircleResolution(100);
ofBackground(255,255,255);
dx = dy = 0;
mydf = NULL;
}


void testApp::updateTuioCursor(int32 id, float xpos,float ypos,float xspeed,float yspeed,float maccel)
{
    dx = xpos;
    dy = ypos;
}


void testApp::newCursor(int32 id, DirectFinger * df)
{
    mydf = df;
}

void testApp::removeCursor(int32 id)
{
    if(mydf && (mydf->s_id == id))
        mydf = NULL;

}

//--------------------------------------------------------------
void testApp::update(){

}

//--------------------------------------------------------------
void testApp::draw(){
    processTevents();
    if(mydf)
    {
        dx = mydf->xpos;
        dy = mydf->ypos;
        ofSetColor(0xFF0000);
    ofFill();
    ofCircle(dx*WINDOW_WIDTH,dy*WINDOW_HEIGHT,20);
    }

}

//--------------------------------------------------------------
void testApp::keyPressed(int key){

}

//--------------------------------------------------------------
void testApp::keyReleased(int key){

}

//--------------------------------------------------------------
void testApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void testApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
