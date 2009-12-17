#include "ofMain.h"
#include "testApp.h"
#include "ofAppGlutWindow.h"
#include "tuioinput.h"

//========================================================================
int main( ){

    ofAppGlutWindow window;
	ofSetupOpenGL(&window, WINDOW_WIDTH ,WINDOW_HEIGHT, OF_WINDOW);			// <-------- setup the GL context
    //ofSetFrameRate(30);
    ofSetVerticalSync(true);
    tuio::tuioinput t;
    t.init();
    testApp * ta = new testApp();
    ta->equeue = t.getQueue();
	// this kicks off the running of my app
	// can be OF_WINDOW or OF_FULLSCREEN
	// pass in width and height too:
	ofRunApp(ta);

}
