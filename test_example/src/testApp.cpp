#include "testApp.h"
#include "CursorFeedback.hpp"
#include "FigureFeedback.hpp"
#include "AreaGesture.hpp"

class AreaProva: public Area
{
    public:
    bool isInside(float x, float y)
    {
        return (x > y);
    }
};

class AreaProva2: public Area
{
    public:
    bool isInside(float x, float y)
    {
        return (x > 0.5f);
    }
};

//--------------------------------------------------------------
void testApp::Setup(){
    new CursorFeedback(new AreaProva());
    new CursorFeedback(new AreaProva2());
    new FigureFeedback(RoundTableArea::Create());
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
