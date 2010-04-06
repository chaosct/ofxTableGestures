/*

    OF-TangibleFramework . Framework for Taller de Sistemes Interactius I
    Universitat Pompeu Fabra

    Copyright (c) 2009 Carles F. Julià <carles.fernandez@upf.edu>

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

#ifndef INPUTGESTUREDIRECTFINGERS_H_INCLUDED
#define INPUTGESTUREDIRECTFINGERS_H_INCLUDED

#include "InputGesture.hpp"
#include "TEvent.hpp"
#include "tuioApp.hpp"
#include "DirectPoint.hpp"
#include "InputGestureBasicFingers.hpp"
#include <map>

using namespace osc;

namespace tuio
{


class DirectFinger: public DirectPoint
{
    public:
    int32 s_id;
    float xspeed, yspeed, maccel;
};

DeclareEvent(TeventDirectFingersRemoveFinger,int32);
DeclareEvent(TeventDirectFingersNewFinger,int32,DirectFinger *);
DeclareEvent(TeventDirectFingersUpdateFinger,int32);


class InputGestureDirectFingers : public CanBasicFingers < CompositeGesture >
{
    std::map<int32,DirectFinger *> fingers;
    public:
        InputGestureDirectFingers(){}
        void addTuioCursor(int32 id, float xpos,float ypos,float xspeed,float yspeed,float maccel)
        {
            DirectFinger * e = new DirectFinger();
            e->s_id = id;
            e->setX(xpos);
            e->setY(ypos);
            e->xspeed = xspeed;
            e->yspeed = yspeed;
            e->maccel = maccel;
            fingers[id]=e;
            TeventDirectFingersNewFinger * evt = makeEvent(TeventDirectFingersNewFinger,(id,e));
            events.push_back(evt);
        }
        void updateTuioCursor(int32 id, float xpos,float ypos,float xspeed,float yspeed,float maccel)
        {
             DirectFinger * e = fingers[id];
            e->s_id = id;
            e->set(xpos,ypos);
            e->xspeed = xspeed;
            e->yspeed = yspeed;
            e->maccel = maccel;
            events.push_back(makeEvent(TeventDirectFingersUpdateFinger,(id)));
        }
        void removeTuioCursor(int32 id)
        {
             TeventDirectFingersRemoveFinger * evt = makeEvent(TeventDirectFingersRemoveFinger,(id));
             events.push_back(evt);
        }
};




template <class Base>
class CanDirectFingers : public  Base
{
    public:
    //Interface redefined by ofApp
    virtual void newCursor(int32 id, DirectFinger *){}
    virtual void removeCursor(int32 id){}
    virtual void updateCursor(int32 id){}

    //registering
    CanDirectFingers()
    {
        TeventDirectFingersRemoveFinger::registerCallback(this,&CanDirectFingers::removeCursor);
        TeventDirectFingersNewFinger::registerCallback(this,&CanDirectFingers::newCursor);
        TeventDirectFingersUpdateFinger::registerCallback(this,&CanDirectFingers::updateCursor);
        Base::template registerIG<InputGestureDirectFingers>();
    }

};


}
#endif // INPUTGESTUREDIRECTFINGERS_H_INCLUDED
