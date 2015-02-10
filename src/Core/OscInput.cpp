#include "OscInput.hpp"

ofEvent<OscInput::EventNewOscMessageArgs> OscInput::EventNewOscMessage;

OscInput::OscInput(){
    oscReceiver.setup(ofxGlobalConfig::getRef("INPUT:TUIO:PORT",3333));
    redirectOSC = ofxGlobalConfig::getRef("INPUT:TUIO:REDIRECT:ACTIVE",0);
    if (redirectOSC){
        oscSender.setup(
            ofxGlobalConfig::getRef<string>("INPUT:TUIO:REDIRECT:HOST","localhost"),
            ofxGlobalConfig::getRef("INPUT:TUIO:REDIRECT:PORT",3334));
    }
}

void OscInput::update(){
    while(oscReceiver.hasWaitingMessages()){
        ofxOscMessage m;
        oscReceiver.getNextMessage(&m);
        EventNewOscMessageArgs args;
        args.m = m;
        ofNotifyEvent(EventNewOscMessage, args);
        if(redirectOSC){
            oscSender.sendMessage(m);
        }
    }
}

