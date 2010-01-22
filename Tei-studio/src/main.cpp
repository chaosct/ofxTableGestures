#include "ofMain.h"
#include "testApp.h"
#include "ofAppGlutWindow.h"


int main( ){
    ///Define the application window
    ofAppGlutWindow window;
    //Window, screen_width, screen height, screen mode
	ofSetupOpenGL(&window, 1024 ,768, OF_WINDOW);			// <-------- setup the GL context
	//for having 100% full screen you must change the previous
	//declaration for this one:
	//ofSetupOpenGL(&window, 1024 ,768, OF_GAME_MODE);
    /// starts the main loop
    ofRunApp(new testApp());
}
