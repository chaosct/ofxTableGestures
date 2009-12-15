#ifndef _TEST_APP
#define _TEST_APP


#include "ofMain.h"

#include "EventQueue.h"

#define WINDOW_HEIGHT 768
#define WINDOW_WIDTH 1024

class testApp : public ofBaseApp{
    private:
        void processTevents();
	public:
        tuio::EventQueue * equeue;
		void setup();
		void update();
		void draw();

		void keyPressed  (int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void windowResized(int w, int h);

};

#endif
