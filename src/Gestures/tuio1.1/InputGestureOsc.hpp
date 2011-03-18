#ifndef INPUTGESTUREOSC_HPP_INCLUDED
#define INPUTGESTUREOSC_HPP_INCLUDED

#include "ofxGlobalConfig.hpp"
#include "Events.hpp"
#include "Singleton.hpp"
#include "Graphic.hpp"
#include "ofxOsc.h"

class InputGestureOSC : public Singleton<InputGestureOSC>, public Graphic
{
    ofxOscReceiver OscReceiver;
    public:
    struct EventNewOScMessageArgs: public EventArgs
    {
        ofxOscMessage m;
    };
    ofEvent<EventNewOScMessageArgs> EventNewOScMessage;
    
    InputGestureOSC()
    {
        OscReceiver.setup(ofxGlobalConfig::getRef("INPUT:TUIO:PORT",3333));
    }
    void update()
    {
        while(OscReceiver.hasWaitingMessages())
        {
            ofxOscMessage m;
            OscReceiver.getNextMessage(&m);

                EventNewOScMessageArgs args;
                args.m = m;
                ofNotifyEvent(EventNewOScMessage,args);


        }
    }
    
};

#endif // INPUTGESTUREOSC_HPP_INCLUDED
