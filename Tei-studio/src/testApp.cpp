#include "testApp.h"
#include <algorithm>
#include "tuioApp.h"
#include "GraphicDispatcher.hpp"
#include "ofxOscSender.h"

class oscNote : public ShowObjectSlider<Tangible<4> >
{
    public:
    ofxOscSender sender;
    oscNote()
    {
        sender.setup("127.0.0.1",9999);
    }
    void sliderValueUpdated(double n)
    {
        ofxOscMessage message;
        message.setAddress("/freq");
        message.addFloatArg(n*440.0 + 440.0);
        sender.sendMessage(message);
    }
};

//--------------------------------------------------------------
void testApp::Setup(){
    ///Init all aplication data
    //listener = new dummylistener();
    //dummygraphic = new dummyGraphic();
    //dummylistenergraphic = new dummyListenerGraphic();
    cursorfeedback = new CursorFeedback();
    figureFeedback = new FigureFeedback();
    tangible_with_a_white_arrow = new ShowAngleArrow< Tangible<3> , 25 >;
    new oscNote();
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

