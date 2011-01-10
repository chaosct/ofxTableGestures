#include "testApp.h"
#include "CursorFeedback.hpp"
#include "FigureFeedback.hpp"
#include "TapFeedback.hpp"
#include "Calibrator.hpp"

//--------------------------------------------------------------
void testApp::Setup(){
    new CursorFeedback();
    new FigureFeedback();
    new TapFeedback();
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
