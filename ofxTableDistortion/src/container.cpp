#include "container.hpp"
#include "Shapes.hpp"

using namespace shapes;
using namespace simulator;

void object::Draw(){
    ofSetLineWidth(0.2f);
    ofPushMatrix();
    ofTranslate(xpos,ypos);
    ofRotateZ(angle*180/PI);
    //Stroke
    ofPushMatrix();
    ofScale(0.91f,0.91f,1.0f);
    if(!isUp){
        ofNoFill();
        ofSetColor(80,80,80,90);
        Figure_shape::Instance().drawShape(fid,false);
        ofFill();
    }
    ofEnableAlphaBlending();
    ofSetColor(100,100,200,90);
    //body
    Figure_shape::Instance().drawShape(fid,false);
    ofPopMatrix();
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
