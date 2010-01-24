#include "testApp.h"
#include <algorithm>
#include "tuioApp.h"
#include "GraphicDispatcher.hpp"

//--------------------------------------------------------------
void testApp::Setup(){
    ///Init all aplication data
    //listener = new dummylistener();
    //dummygraphic = new dummyGraphic();
    //dummylistenergraphic = new dummyListenerGraphic();
    cursorfeedback = new CursorFeedback();
    figureFeedback = new FigureFeedback();
    tangible_with_a_white_arrow = new ShowAngleArrow< SpinsPerAngle < Tangible<3> , 2 > , 25 >;
    new ShowObjectSlider<Tangible<4> >;
}

//--------------------------------------------------------------
void testApp::Update(){
    ///Update graphic data, with this command all update methods from all 'Graphics' are launched
    GraphicDispatcher::Instance().Update();
    ///Update input events, it says to all input gestures to process the gesture stack.
    tuio::Dispatcher::Instance().processTevents();
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

