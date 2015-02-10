#ifndef INPUTGESTUREOSC_HPP_INCLUDED
#define INPUTGESTUREOSC_HPP_INCLUDED

#include "ofxGlobalConfig.hpp"
#include "Events.hpp"
#include "ofxOsc.h"

class OscInput{
    public:
	struct EventNewOscMessageArgs : public EventArgs{
	    ofxOscMessage m;
	};
        static ofEvent<EventNewOscMessageArgs> EventNewOscMessage;
        OscInput();
        void update();

    private:
        ofxOscReceiver oscReceiver;
        ofxOscSender oscSender;
        bool redirectOSC;
};

#endif // INPUTGESTUREOSC_HPP_INCLUDED
