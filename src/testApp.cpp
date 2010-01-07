#include "testApp.h"
#include "TEvent.h"
#include "tuioinput.h"



//--------------------------------------------------------------
void testApp::Setup(){

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

void testApp::newObject(int32 s_id, int32 f_id, DirectObject * dob)
{
    mdo = dob;
}
void testApp::removeObject(int32 s_id, int32 f_id)
{
    if(mdo && (mdo->s_id == s_id))
        mdo = NULL;
}


//--------------------------------------------------------------
void testApp::Update(){

}

//--------------------------------------------------------------
void testApp::Draw(){
    processTevents();

    if(mydf)
    {
        dx = mydf->xpos;
        dy = mydf->ypos;
        ofSetColor(0xFF0000);
    ofFill();
    ofCircle(dx*ofGetWidth(),dy*ofGetHeight(),20);
    }
    if(mdo)
    {
        dx = mdo->xpos;
        dy = mdo->ypos;
        float r = mdo->angle;
        ofSetColor(0xFF0000);
    ofFill();
    ofRotateZ(r);
    ofRect(dx*ofGetWidth(),dy*ofGetHeight(),40,40);
    }

}

//--------------------------------------------------------------
void testApp::WindowResized(int w, int h){

}

//--------------------------------------------------------------
