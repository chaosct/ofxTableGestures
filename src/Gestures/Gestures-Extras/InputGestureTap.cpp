#include "InputGestureTap.hpp"

ofEvent<InputGestureTap::TapArgs> InputGestureTap::Tap;

InputGestureTap::InputGestureTap() :
        maxdistance(ofxGlobalConfig::getRef("GESTURES:TAP:MAXDISTANCE", 0.002f)),
        maxtime(ofxGlobalConfig::getRef("GESTURES:TAP:MAXTIME", 0.2f)){
    registerEvent(InputGestureDirectFingers::newCursor, &InputGestureTap::newCursor);
    registerEvent(InputGestureDirectFingers::removeCursor, &InputGestureTap::removeCursor);
}

void InputGestureTap::newCursor(InputGestureDirectFingers::newCursorArgs & a){
    DirectFinger * f = a.finger;
    float now = ofGetElapsedTimef();
    previous[f]= make_pair(ofVec2f(f->x, f->y), now);
}

void InputGestureTap::removeCursor(InputGestureDirectFingers::removeCursorArgs & a){
    DirectFinger * f = a.finger;
    if(previous.find(f) != previous.end()){
        float now = ofGetElapsedTimef();
        if (previous[f].second > (now - maxtime) &&
            previous[f].first.distance(*f) <= maxdistance){
            TapArgs eventargs;
            eventargs.x = f->x;
            eventargs.y = f->y;
            eventargs.target = a.target;
            ofNotifyEvent(Tap, eventargs);
        }
        previous.erase(f);
    }
}

