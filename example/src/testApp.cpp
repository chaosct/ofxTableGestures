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

        polygon.SetTexture("temp.png");

        std::cout<< polygon.GetTriangleNumber() << std::endl;
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
        //polygon.DrawStroke();
        ofPopMatrix();
    }

    void updatecursor(InputGestureBasicFingers::updateTuioCursorArgs &args)
    {
        if( polygon.Collide(ofPoint(args.xpos,args.ypos)))
        {
            color.r = 255;
            color.g = 0;
            color.b = 0;
            this->unregisterEvent(InputGestureBasicFingers::Instance().updateTuioCursor);
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

class Test2: public Graphic
{
    public:
    Test2()
    {
        registerEvent(InputGestureBasicFingers::Instance().addTuioCursor, &Test2::genericCallback);
    }
    void genericCallback(InputGestureBasicFingers::addTuioCursorArgs & e)
    {
        std::cout << "addTuioCursor " << e.target << std::endl;
    }
    bool Collide(ofPoint const & point)
    {
        ofPoint d = point - ofPoint(0.5,0.5);
        d = d*d;
        std::cout << sqrt(d.x+d.y) << std::endl;
        if (sqrt(d.x+d.y) < 0.02)
            return true;
        return false;
    }
};

#include "Triangulate.h"

//--------------------------------------------------------------
void testApp::setup(){

    tableapp.setup();

    //tuioBundles::Instance();
    //new test();
    //new Test2();
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

