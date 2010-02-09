#include "testApp.h"
#include "CursorFeedback.h"
#include "FigureFeedback.h"

//--------------------------------------------------------------
void testApp::Setup(){
    new CursorFeedback();
    new FigureFeedback();
}

//--------------------------------------------------------------
void testApp::Update(){

}

//--------------------------------------------------------------
void testApp::Draw(){

}

//--------------------------------------------------------------
void testApp::WindowResized(int w, int h){

}
