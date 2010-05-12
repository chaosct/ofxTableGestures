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
    new CalibratorObject(1);
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
