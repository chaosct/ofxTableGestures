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

class InputGestureLongPush : public EventClient{
    public:
        struct LongPushTriggerArgs : public EventArgs{
            float x;
            float y;
        };
        static ofEvent<LongPushTriggerArgs> LongPushTrigger;

        InputGestureLongPush();
        void update(float & now);
        virtual void newCursor(InputGestureDirectFingers::newCursorArgs & a);
        virtual void updateCursor(InputGestureDirectFingers::updateCursorArgs & a);
        virtual void removeCursor(InputGestureDirectFingers::removeCursorArgs & a);

    private:
        float & maxdistance;
        float & mintime;
        std::map< DirectFinger *,  std::pair < ofVec2f , float > > previous;
};

template<class Base>
class CanLongPush: public Base
{
public:
    //Interface redefined by ofApp
    void ELongPushTrigger(InputGestureLongPush::LongPushTriggerArgs & eventargs)
    {
        LongPushTrigger(eventargs.x,eventargs.y);
  }
    virtual void LongPushTrigger(float x, float y) {}

    CanLongPush()
  {
        ofAddListener(InputGestureLongPush::LongPushTrigger,this,&CanLongPush::ELongPushTrigger);
    }
    virtual ~CanLongPush()
    {
        ofRemoveListener(InputGestureLongPush::LongPushTrigger,this,&CanLongPush::ELongPushTrigger);
    }
};

#endif // INPUTGESTUREKEEP_HPP_INCLUDED
