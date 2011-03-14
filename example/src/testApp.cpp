#include "testApp.h"

#include "CursorFeedback.hpp"
#include "FigureFeedback.hpp"
#include "HandFeedback.hpp"
#include "TapFeedback.hpp"
#include "LongPushFeedback.hpp"
#include "Polygon.h"
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

    Figures::Polygon polygon;
    polygon.AddVertex(ofPoint(-0.05f, -0.05f));
    polygon.AddVertex(ofPoint(-0.05f, 0.05f));
    polygon.AddVertex(ofPoint(0.05f, 0.05f));
    polygon.AddVertex(ofPoint(0.05f, 0.025f));
    polygon.AddVertex(ofPoint(-0.025f, 0.025f));
    polygon.AddVertex(ofPoint(-0.025f, -0.025f));
    polygon.AddVertex(ofPoint(0.025f, -0.025f));
    polygon.AddVertex(ofPoint(0.025f, 0.0f));
    polygon.AddVertex(ofPoint(0.05f, 0.0f));
    polygon.AddVertex(ofPoint(0.05f, -0.05f));
    polygon.Collide(ofPoint(0,0));
    std::cout<< polygon.GetTriangleNumber() << std::endl;
}

//--------------------------------------------------------------
void testApp::update(){


}

//--------------------------------------------------------------
void testApp::draw(){
    tableapp.draw();
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

