#include "testApp.h"
#include <algorithm>
#include "tuioApp.h"
#include "GraphicDispatcher.hpp"

//--------------------------------------------------------------
void testApp::Setup(){
    //Singleton<Dispatcher>::Instance().AddListener((Listener*)this);
    listener = new tuio::dummylistener();
    listener2 = new tuio::dummylistener2();
    cursorfeedback = new CursorFeedback();
    figureFeedback = new FigureFeedback();
}

//--------------------------------------------------------------
void testApp::Update(){
    //processem els gestos
    GraphicDispatcher::Instance().Update();
    tuio::Dispatcher::Instance().processTevents();
}

//--------------------------------------------------------------
void testApp::Draw(){
    GraphicDispatcher::Instance().Draw();
}

//--------------------------------------------------------------
void testApp::WindowResized(int w, int h){
    GraphicDispatcher::Instance().Resize(w,h);
}

//--------------------------------------------------------------

