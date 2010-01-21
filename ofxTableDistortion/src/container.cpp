#include "container.hpp"

using namespace simulator;

void object::Draw(){
    ofPushMatrix();
    ofTranslate(xpos,ypos);
    ofRotateZ(angle*180/PI);
    //Stroke
    if(!isUp){
        ofNoFill();
        ofSetColor(80,80,80);
        //ofCircle(0,0,OBJECT_RADIUS*ofGetHeight()/2);
        Figure_shape::Instance().drawShape(fid,false);
        ofFill();
    }
    ofEnableAlphaBlending();
    ofSetColor(100,100,200,200);
    //body
    //ofCircle(0,0,OBJECT_RADIUS*ofGetHeight()/2);
    Figure_shape::Instance().drawShape(fid,false);
    ofSetColor(255,0,0);
    //rotation line
    ofPushMatrix();
    ofLine(0,0,0,OBJECT_RADIUS*ofGetHeight()/2);
    ofPopMatrix();
    ofDisableAlphaBlending();
    ofSetColor(0xFFFFFF);
    std::stringstream msg;
    msg << fid;
    //text
    ofDrawBitmapString(msg.str(), 0, 0);
    ofPopMatrix();
}
