#ifndef INPUTGESTUREKEEP_HPP_INCLUDED
#define INPUTGESTUREKEEP_HPP_INCLUDED

#include "InputGestureDirectFingers.hpp"
#include "InputGestureTuio1.1fseq.hpp"
/*

    OF-TangibleFramework . Framework for Taller de Sistemes Interactius I
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

#include <map>
#include <algorithm>

namespace tuio
{
    SimpleDeclareEvent(CanLongPush,LongPushTriger,float,float);

    class InputGestureLongPush: public CanTuio11ValidBundle< CanDirectFingers< CompositeGesture > >
    {
        float & maxdistance;
        float & mintime;
        std::map< DirectFinger *,  std::pair < DirectPoint , float > > previous;
        public:
        InputGestureLongPush():
            maxdistance(GlobalConfig::getRef("GESTURES:KEEP:MAXDISTANCE",0.005f)),
            mintime(GlobalConfig::getRef("GESTURES:KEEP:MINTIME",1.0f)){}
        virtual void newCursor(DirectFinger * f)
        {
            float now = ofGetElapsedTimef();
            previous[f]= make_pair(DirectPoint(f->getX(),f->getY()),now);
        }

        void isvalid(bool v)
        {
            float now = ofGetElapsedTimef();
            std::map< DirectFinger *,  std::pair < DirectPoint , float > >::iterator iter = previous.begin();
            for(;iter!=previous.end();)
            {
                if((now - iter->second.second) > mintime)
                {
                    SimpleCallEvent(CanLongPush,LongPushTriger,(iter->first->getX(),iter->first->getY()));
                    previous.erase(iter++);
                }
                else
                {
                    ++iter;
                }
            }
        }

        virtual void updateCursor(DirectFinger *f)
        {
            if(previous.find(f) != previous.end())
            {
                if (previous[f].first.getDistance(f) > maxdistance)
                    {
                         previous.erase(f);
                    }
            }
        }
        virtual void removeCursor(DirectFinger *f)
        {
            if(previous.find(f) != previous.end())
            {
                previous.erase(f);
            }
        }

        virtual void enterCursor(DirectFinger *df){}
        virtual void exitCursor(DirectFinger *f)
        {
            previous.erase(f);
        }
    };

    template<class Base>
    class CanLongPush: public Base
    {
        public:
        //Interface redefined by ofApp
        virtual void LongPushTriger(float x, float y){}

        void Register(Area * a)
        {
            Base::Register(a);
            SimpleRegisterEvent(CanLongPush, LongPushTriger);
            Base::template registerIG<InputGestureLongPush>();
        }
    };

}

#endif // INPUTGESTUREKEEP_HPP_INCLUDED
