/*

    ofxTableGestures (formerly OF-TangibleFramework)
    Developed for Taller de Sistemes Interactius I
    Universitat Pompeu Fabra

    Copyright (c) 2010 Carles F. Julià <carles.fernandez@upf.edu>

    Permission is hereby granted, free of charge, to any person
    obtaining a copy of this software and associated documentation
    files (the "Software"), to deal in the Software without
    restriction, including without limitation the rights to use,
    copy, modify, merge, publish, distribute, sublicense, and/or sell
    copies of the Software, and to permit persons to whom the
    Software is furnished to do so, subject to the following
    conditions:

    The above copyright notice and this permission notice shall be
    included in all copies or substantial portions of the Software.

    THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
    EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES
    OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
    NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT
    HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
    WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
    FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
    OTHER DEALINGS IN THE SOFTWARE.

*/

#ifndef INPUTGESTUREKEEP_HPP_INCLUDED
#define INPUTGESTUREKEEP_HPP_INCLUDED

#include "InputGestureDirectFingers.hpp"
#include <map>
#include <algorithm>
#include "Alarm.hpp"

class InputGestureLongPush: public EventClient , public Singleton<InputGestureLongPush>
{
    float & maxdistance;
    float & mintime;
    std::map< DirectFinger *,  std::pair < DirectPoint , float > > previous;
public:
    struct LongPushTrigerArgs : public EventArgs
    {
        float x;
        float y;
    };
    ofEvent<LongPushTrigerArgs> LongPushTriger;
    InputGestureLongPush():
        maxdistance(ofxGlobalConfig::getRef("GESTURES:KEEP:MAXDISTANCE",0.005f)),
        mintime(ofxGlobalConfig::getRef("GESTURES:KEEP:MINTIME",1.0f))
        {
            registerEvent(InputGestureDirectFingers::Instance().newCursor,&InputGestureLongPush::newCursor);
            registerEvent(InputGestureDirectFingers::Instance().updateCursor,&InputGestureLongPush::updateCursor);
            registerEvent(InputGestureDirectFingers::Instance().removeCursor,&InputGestureLongPush::removeCursor);
        }
    virtual void newCursor(InputGestureDirectFingers::newCursorArgs & a)
    {
        DirectFinger * f = a.finger;
        float now = ofGetElapsedTimef();
        previous[f]= make_pair(DirectPoint(f->getX(),f->getY()),now);
        Alarm::Setup(now+mintime,this,&InputGestureLongPush::update);
    }

    void update(float & now)
    {
        std::map< DirectFinger *,  std::pair < DirectPoint , float > >::iterator iter = previous.begin();
        for(; iter!=previous.end();)
        {
            if((now - iter->second.second) > mintime)
            {
                LongPushTrigerArgs eventargs;
                eventargs.x = iter->first->getX();
                eventargs.y = iter->first->getY();
                ofNotifyEvent(LongPushTriger,eventargs);

                previous.erase(iter++);
            }
            else
            {
                ++iter;
            }
        }
    }
    virtual void updateCursor(InputGestureDirectFingers::updateCursorArgs & a)
    {
        DirectFinger * f = a.finger;
        if(previous.find(f) != previous.end())
        {
            if (previous[f].first.getDistance(f) > maxdistance)
            {
                previous.erase(f);
            }
        }
    }
    virtual void removeCursor(InputGestureDirectFingers::removeCursorArgs & a)
    {
        DirectFinger * f = a.finger;
        if(previous.find(f) != previous.end())
        {
            previous.erase(f);
        }
    }

};

template<class Base>
class CanLongPush: public Base
{
public:
    //Interface redefined by ofApp
    void ELongPushTriger(InputGestureLongPush::LongPushTrigerArgs & eventargs)
    {
        LongPushTriger(eventargs.x,eventargs.y);
    }
    virtual void LongPushTriger(float x, float y) {}

    CanLongPush()
    {
        ofAddListener(InputGestureLongPush::Instance().LongPushTriger,this,&CanLongPush::ELongPushTriger);
    }
    virtual ~CanLongPush()
    {
        ofRemoveListener(InputGestureLongPush::Instance().LongPushTriger,this,&CanLongPush::ELongPushTriger);
    }
};



#endif // INPUTGESTUREKEEP_HPP_INCLUDED
