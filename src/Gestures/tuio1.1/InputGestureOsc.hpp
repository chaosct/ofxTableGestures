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
    ofxOscSender OscSender;
    bool redirectOSC;
    public:
    struct EventNewOScMessageArgs: public EventArgs
    {
        ofxOscMessage m;
    };
    ofEvent<EventNewOScMessageArgs> EventNewOScMessage;
    
    InputGestureOSC()
    {
        OscReceiver.setup(ofxGlobalConfig::getRef("INPUT:TUIO:PORT",3333));
        redirectOSC = ofxGlobalConfig::getRef("INPUT:TUIO:REDIRECT:ACTIVE",0);
        if(redirectOSC)
        {
            OscSender.setup(
                ofxGlobalConfig::getRef<string>("INPUT:TUIO:REDIRECT:HOST","localhost"),
                ofxGlobalConfig::getRef("INPUT:TUIO:REDIRECT:PORT",3334)
                );
        }
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

            if(redirectOSC)
            {
                OscSender.sendMessage(m);
            }
        }
    }
    
};

#endif // INPUTGESTUREOSC_HPP_INCLUDED
