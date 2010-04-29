/*

    TSIframework . Framework for Taller de Sistemes Interactius I
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

#ifndef INPUTGESTURETAP_HPP_INCLUDED
#define INPUTGESTURETAP_HPP_INCLUDED

#include "InputGestureDirectFingers.hpp"

namespace tuio
{

SimpleDeclareEvent(CanTap,Tap,float,float);

class InputGestueTap : public CanDirectFingers < CompositeGesture >
{
    float & maxdistance;
    float & maxtime;
    std::map< DirectFinger *,  std::pair < DirectPoint , float > > previous;

    public:
    InputGestueTap():
    maxdistance(GlobalConfig::getRef("GESTURES:TAP:MAXDISTANCE",0.002f)),
    maxtime(GlobalConfig::getRef("GESTURES:TAP:MAXTIME",0.2f)){}

    virtual void newCursor(DirectFinger * f)
    {
        float now = ofGetElapsedTimef();
        previous[f]= make_pair(DirectPoint(f->getX(),f->getY()),now);
    }
    virtual void removeCursor(DirectFinger *f)
    {
        if(previous.find(f) != previous.end())
        {
            float now = ofGetElapsedTimef();
            if (previous[f].second > (now - maxtime) &&
                previous[f].first.getDistance(f) <= maxdistance)
                {
                    SimpleCallEvent(CanTap,Tap,(f->getX(),f->getY()));
                }
            previous.erase(f);
        }
    }
    virtual void updateCursor(DirectFinger *){}
    //Area-aware interface optionally redefined by ofApp
    virtual void enterCursor(DirectFinger *df){}
    virtual void exitCursor(DirectFinger *f)
    {
        previous.erase(f);
    }
};


template<class Base>
class CanTap: public Base
{
    public:
    //Interface redefined by ofApp
    virtual void Tap(float x, float y){}

    void Register(Area * a)
    {
        Base::Register(a);
        SimpleRegisterEvent(CanTap, Tap);
        Base::template registerIG<InputGestueTap>();
    }
};

}

#endif // INPUTGESTURETAP_HPP_INCLUDED
