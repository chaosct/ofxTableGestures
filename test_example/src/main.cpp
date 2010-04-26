#include "ofMain.h"
#include "testApp.h"
#include "ofAppGlutWindow.h"
#include "GlobalConfig.hpp"


int main( ){

    ofAppGlutWindow window;
    int width = GlobalConfig::getRef("PROGRAM:WIDTH",1024);
    int height = GlobalConfig::getRef("PROGRAM:HEIGHT",768);
    if(GlobalConfig::getRef("PROGRAM:FULLSCREEN",0))
        ofSetupOpenGL(&window, width ,height, OF_GAME_MODE);
    else
        ofSetupOpenGL(&window, width ,height, OF_WINDOW);
	ofRunApp( new testApp());
}
