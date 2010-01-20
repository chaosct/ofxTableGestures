#include "testApp.h"
#include <algorithm>
#include "tuioApp.h"

//--------------------------------------------------------------
void testApp::Setup(){
    //Singleton<Dispatcher>::Instance().AddListener((Listener*)this);
    listener = new dummylistener();
    listener2 = new dummylistener2();
    Dispatcher::Instance().tostring();
}

//--------------------------------------------------------------
void testApp::Update(){
    //processem els gestos
    Dispatcher::Instance().processTevents();
}

//--------------------------------------------------------------
void testApp::Draw(){

}

//--------------------------------------------------------------
void testApp::WindowResized(int w, int h){

}

//--------------------------------------------------------------

