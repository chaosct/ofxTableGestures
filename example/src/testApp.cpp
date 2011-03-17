#include "testApp.h"

#include "CursorFeedback.hpp"
#include "FigureFeedback.hpp"
#include "HandFeedback.hpp"
#include "TapFeedback.hpp"
#include "LongPushFeedback.hpp"
#include "InputGestureBasicFingers.hpp"

class test: public Graphic
{
    float r;
    Figures::Polygon polygon;
    ofColor color;
    public:
    test():r(0.2f)
    {
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

        std::cout<< polygon.GetTriangleNumber() << std::endl;
//        ofAddListener(tuioBundles::Instance().EventNewOScMessage,this,&test::bundle);
        this->registerEvent(InputGestureBasicFingers::Instance().updateTuioCursor, &test::updatecursor);
        color.r = 255;
        color.g = 255;
        color.b = 255;
    }
    void draw()
    {
        ofPushMatrix();
        ofFill();
        ofSetColor(color.r,color.g,color.b);
        //ofCircle(0.5,0.5,r);
        ofTranslate(0.5f,0.5f);
        polygon.Draw();
        ofSetColor(255,255,0);
        ofSetLineWidth(2.0f);
        polygon.DrawStroke();
        ofPopMatrix();
    }

    void updatecursor(InputGestureBasicFingers::updateTuioCursorArgs &args)
    {
        if( polygon.Collide(ofPoint(args.xpos,args.ypos)))
        {
            color.r = 255;
            color.g = 0;
            color.b = 0;
        }
        else
        {
            color.r = 255;
            color.g = 255;
            color.b = 255;
        }
    }
//    void bundle(tuioBundles::EventNewOScMessageArgs & args)
//    {
//        r+= 0.001;
//    }
};

#include "Triangulate.h"

//--------------------------------------------------------------
void testApp::setup(){

    tableapp.setup();

    //tuioBundles::Instance();
    new test();
    new CursorFeedback();
    new FigureFeedback();
    new HandFeedback();
    new TapFeedback();
    new LongPushFeedback();
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

