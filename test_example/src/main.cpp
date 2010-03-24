#include "ofMain.h"
#include "testApp.h"
#include "ofAppGlutWindow.h"

//========================================================================
int main( ){

    ofAppGlutWindow window;
    ofSetupOpenGL(&window, 1024 ,768, OF_WINDOW);			// <-------- setup the GL context
	//for having 100% full screen you must change the previous
	//declaration for this one:
	//ofSetupOpenGL(&window, 1024 ,768, OF_GAME_MODE);
	ofRunApp( new testApp());
}
