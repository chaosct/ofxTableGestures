#include "testApp.h"
#include "TEvent.h"

//--------------------------------------------------------------
void testApp::setup(){
ofSetCircleResolution(100);
ofBackground(255,255,255);
}

void testApp::processTevents()
{
    tuio::TEvent * te;
    while((te = equeue->pop())!= NULL)
    {
        std::cout << "Event rebut! " << te->name << std::endl;
        //delete te;
    }
}

//--------------------------------------------------------------
void testApp::update(){

}

//--------------------------------------------------------------
void testApp::draw(){
    processTevents();
    ofSetColor(0xFF0000);
    ofFill();
    ofCircle(100,400,20);
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

