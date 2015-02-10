#include "InputGestureLongPush.hpp"

ofEvent<InputGestureLongPush::LongPushTriggerArgs> InputGestureLongPush::LongPushTrigger;

InputGestureLongPush::InputGestureLongPush() :
        maxdistance(ofxGlobalConfig::getRef("GESTURES:KEEP:MAXDISTANCE", 0.005f)),
        mintime(ofxGlobalConfig::getRef("GESTURES:KEEP:MINTIME", 1.0f)){
    registerEvent(InputGestureDirectFingers::newCursor, &InputGestureLongPush::newCursor);
    registerEvent(InputGestureDirectFingers::updateCursor, &InputGestureLongPush::updateCursor);
    registerEvent(InputGestureDirectFingers::removeCursor, &InputGestureLongPush::removeCursor);
}

void InputGestureLongPush::newCursor(InputGestureDirectFingers::newCursorArgs & a){
    DirectFinger * f = a.finger;
    float now = ofGetElapsedTimef();
    previous[f]= make_pair(ofVec2f(f->x, f->y), now);
    Alarm::Setup(now+mintime, this, &InputGestureLongPush::update);
}

void InputGestureLongPush::update(float & now){
    std::map< DirectFinger *, std::pair<ofVec2f, float> >::iterator iter = previous.begin();
    while (iter!=previous.end()){
        if ((now - iter->second.second) > mintime){
            LongPushTriggerArgs eventargs;
            eventargs.x = iter->first->x;
            eventargs.y = iter->first->y;
            ofNotifyEvent(LongPushTrigger, eventargs);

            previous.erase(iter++);
        }else{
            ++iter;
        }
    }
}

void InputGestureLongPush::updateCursor(InputGestureDirectFingers::updateCursorArgs & a){
    DirectFinger * f = a.finger;
    if (previous.find(f) != previous.end()){
        if (previous[f].first.distance(*f) > maxdistance){
            previous.erase(f);
        }
    }
}

void InputGestureLongPush::removeCursor(InputGestureDirectFingers::removeCursorArgs & a){
    DirectFinger * f = a.finger;
    if (previous.find(f) != previous.end()){
        previous.erase(f);
    }
}

