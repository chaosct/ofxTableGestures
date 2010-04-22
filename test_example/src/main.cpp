#include "ofMain.h"
#include "testApp.h"
#include "ofAppGlutWindow.h"
#include "GlobalConfig.hpp"


int main( ){

    ofAppGlutWindow window;
    if(GlobalConfig::getRef("PROGRAM:FULLSCREEN",0))
        ofSetupOpenGL(&window, 1024 ,768, OF_GAME_MODE);
    else
        ofSetupOpenGL(&window, 1024 ,768, OF_WINDOW);
	ofRunApp( new testApp());
}
