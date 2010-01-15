#include "testApp.h"
#include <algorithm>

//--------------------------------------------------------------
void testApp::Setup(){

}

//--------------------------------------------------------------
void testApp::Update(){

}

bool canremove(Ring * r)
{
    return r->canremove();
}

//--------------------------------------------------------------
void testApp::Draw(){
    //processem els gestos
    processTevents();
    MyTimer::Instance().step();
    for (Tcursors::iterator it = cursors.begin(); it != cursors.end(); ++it)
    {
        DirectFinger * df = it->second;
        if(df)
        {
            float dx = df->xpos;
            float dy = df->ypos;
            ofSetColor(0xFF0000);
            ofFill();
            ofCircle(dx*ofGetWidth(),dy*ofGetHeight(),10);
        }
    }

    for (Tobjects::iterator it = objects.begin(); it != objects.end(); ++it)
    {
        DirectObject * dob = it->second;
        if(dob)
        {
            float dx = dob->xpos;
            float dy = dob->ypos;
            float a = dob->angle;
            ofSetColor(0xFF0000);
            ofFill();
            ofPushMatrix();
            ofTranslate(dx*ofGetWidth(),dy*ofGetHeight(),0);
            ofRotateZ(a*180.0/PI);
            ofRect(-40,-40,80,80);
            ofPopMatrix();
        }
    }
    for (std::list<Ring *>::iterator it = rings.begin(); it != rings.end(); ++it)
    {
        (*it)->Draw();
    }
    std::list<Ring *>::iterator nend = remove_if(rings.begin(),rings.end(),canremove);
    rings.erase(nend,rings.end());

}

//--------------------------------------------------------------
void testApp::WindowResized(int w, int h){

}

//--------------------------------------------------------------

void testApp::newCursor(int32 id, DirectFinger * df)
{
    cursors[id]=df;

}

void testApp::removeCursor(int32 id)
{
    cursors[id]=NULL;
}

void testApp::newObject(int32 s_id, int32 f_id, DirectObject * dob)
{
    objects[s_id]=dob;
}

void testApp::removeObject(int32 s_id, int32 f_id)
{
    objects[s_id]=NULL;
}

void testApp::click(float x, float y)
{
    rings.push_back(new Ring(x*ofGetWidth(),y*ofGetHeight()));
}
