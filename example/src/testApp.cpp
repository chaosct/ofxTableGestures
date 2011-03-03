#include "testApp.h"

#include "CursorFeedback.hpp"
#include "FigureFeedback.hpp"
#include "HandFeedback.hpp"
#include "TapFeedback.hpp"
#include "LongPushFeedback.hpp"

//class test: public Graphic
//{
//    float r;
//    public:
//    test():r(0)
//    {
//        ofAddListener(tuioBundles::Instance().EventNewOScMessage,this,&test::bundle);
//    }
//    void draw()
//    {
//        ofSetColor(255,0,0);
//        ofCircle(0.5,0.5,r);
//    }
//    void bundle(tuioBundles::EventNewOScMessageArgs & args)
//    {
//        r+= 0.001;
//    }
//};

//--------------------------------------------------------------
void testApp::setup(){

    tableapp.setup();

    //tuioBundles::Instance();
    //new test();
    new CursorFeedback();
    new FigureFeedback();
    new HandFeedback();
    new TapFeedback();
    new LongPushFeedback();
    
}

//--------------------------------------------------------------
void testApp::update(){

    tableapp.update();
}

//--------------------------------------------------------------
void testApp::draw(){
    tableapp.draw();
}

//--------------------------------------------------------------
void testApp::keyPressed(int key){
    tableapp.keyPressed(key);
}

//--------------------------------------------------------------
void testApp::keyReleased(int key){
    tableapp.keyReleased(key);
}

//--------------------------------------------------------------
void testApp::mouseMoved(int x, int y ){
    tableapp.mouseMoved(x,y);
}

//--------------------------------------------------------------
void testApp::mouseDragged(int x, int y, int button){
    tableapp.mouseDragged(x,y,button);
}

//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button){
    tableapp.mousePressed( x,  y,  button);
}

//--------------------------------------------------------------
void testApp::mouseReleased(int x, int y, int button){
    tableapp.mouseReleased( x,  y,  button);
}

//--------------------------------------------------------------
void testApp::windowResized(int w, int h){
    tableapp.windowResized( w,  h);
}

