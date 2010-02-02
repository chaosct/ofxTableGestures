#include "testApp.h"
#include <algorithm>
#include "tuioApp.h"
#include "Dispatcher.h"
#include "GraphicDispatcher.hpp"
#include "ofxOscSender.h"


testApp::~testApp(){
    delete sine;
    delete angle_arrow_marked;
    delete tangible_with_a_white_arrow;
    delete figureFeedback;
    delete cursorfeedback;
}

//--------------------------------------------------------------
void testApp::Setup(){
    ///Init all aplication data
    cursorfeedback = new CursorFeedback();
    figureFeedback = new FigureFeedback();
    tangible_with_a_white_arrow = new ShowAngleArrow< Tangible<3> , 25 >;
    angle_arrow_marked = new proto1;
    sine = new oscNote();
    new runtimeGenerator();
}

//--------------------------------------------------------------
void testApp::Update(){
    ///Update input events, it says to all input gestures to process the gesture stack.
    tuio::Dispatcher::Instance().processTevents();
    ///Update graphic data, with this command all update methods from all 'Graphics' are launched
    GraphicDispatcher::Instance().Update();
}

//--------------------------------------------------------------
void testApp::Draw(){
    ///Draws all 'Graphics'
    GraphicDispatcher::Instance().Draw();
}

//--------------------------------------------------------------
void testApp::WindowResized(int w, int h){
    ///calls resize method of all 'Graphics' when nedded.
    GraphicDispatcher::Instance().Resize(w,h);
}

//--------------------------------------------------------------

