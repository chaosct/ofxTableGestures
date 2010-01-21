#include "testApp.h"
#include <algorithm>
#include "tuioApp.h"

#include "Shapes.hpp"
//--------------------------------------------------------------
void testApp::Setup(){
    //Singleton<Dispatcher>::Instance().AddListener((Listener*)this);
    listener = new dummylistener();
    listener2 = new dummylistener2();
    cursorfeedback = new CursorFeedback();
}

//--------------------------------------------------------------
void testApp::Update(){
    //processem els gestos
    Dispatcher::Instance().processTevents();
    cursorfeedback->Update();
}

//--------------------------------------------------------------
void testApp::Draw(){
    cursorfeedback->Draw();
}

//--------------------------------------------------------------
void testApp::WindowResized(int w, int h){

}

//--------------------------------------------------------------

