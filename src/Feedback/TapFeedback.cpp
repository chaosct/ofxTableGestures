#include "TapFeedback.hpp"

TapFeedback::TapFeedback() : lifetime(ofxGlobalConfig::getRef("FEEDBACK:TAP:DURATION",1.0f)),
                            maxradius(ofxGlobalConfig::getRef("FEEDBACK:TAP:MAXRADIUS",0.1f)){
    registerEvent(InputGestureTap::Tap, &TapFeedback::Tap);
}

void TapFeedback::Tap(InputGestureTap::TapArgs & args){
    // Delete old taps
    float actualTime = ofGetElapsedTimef();
    while (taps.size() > 0 && (actualTime - taps.front()->getBornTime() > lifetime)){
        delete taps.front();
        taps.pop();
    }

    // Create new tap
    CircleTap* newTap = new CircleTap(ofVec2f(args.x, args.y), maxradius, lifetime);
    taps.push(newTap);
}


// CircleTap subclass //////////
TapFeedback::CircleTap::CircleTap(const ofVec2f& dp, float r, float lt) :
    born(ofGetElapsedTimef()),
    lifetime(lt),
    maxradius(r),
    p(dp) {}

float TapFeedback::CircleTap::getBornTime(){
    return born;
}

void TapFeedback::CircleTap::draw(){
    static int & R = ofxGlobalConfig::getRef("FEEDBACK:CURSOR:COLOR:R",255);
    static int & G = ofxGlobalConfig::getRef("FEEDBACK:CURSOR:COLOR:G",0);
    static int & B = ofxGlobalConfig::getRef("FEEDBACK:CURSOR:COLOR:B",0);

    float now = ofGetElapsedTimef();
    float alpha = ((now - born) / lifetime);
    float radius = alpha * maxradius ;
    int alpha255 = (int)((1.0f-alpha)*255);
    ofPushStyle();
    ofNoFill();
    ofSetLineWidth(4);
    ofSetColor(R,G,B,alpha255);
    ofEnableAlphaBlending();
    ofCircle(p.x,p.y,radius);
    ofDisableAlphaBlending();
    ofPopStyle();
}
///////////////////////////

