/*

    TSIframework . Framework for Taller de Sistemes Interactius I
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

#ifndef TUIO_INPUTGESTUREBASICFINGERS_H
#define TUIO_INPUTGESTUREBASICFINGERS_H

#include "osc/OscReceivedElements.h"
#include "InputGesture.h"
#include "TEvent.h"
#include <set>
#include "tuioApp.h"
using namespace osc;

namespace tuio {

class TeventBasicFingersRemoveFinger : public TEvent
{
    public:
    TeventBasicFingersRemoveFinger():TEvent(event_finger_remove){}
    int32 s_id;
};

class TeventBasicFingersNewFinger : public TEvent
{
    public:
    TeventBasicFingersNewFinger():TEvent(event_finger_new){}
    int32 s_id;
    float xpos, ypos, xspeed, yspeed, maccel;
};

class TeventBasicFingersMoveFinger : public TEvent
{
    public:
    TeventBasicFingersMoveFinger():TEvent(event_finger_move){}
    int32 s_id;
    float xpos, ypos, xspeed, yspeed, maccel;
};

class InputGestureBasicFingers : public InputGesture {
    std::set<int32> s_ids;
    int32 currentFrame, lastFrame;
    public:
        InputGestureBasicFingers():currentFrame(0),lastFrame(0){}
        virtual void ReceiveCall(const char * addr, osc::ReceivedMessageArgumentStream & argList);
};

template <class Base>
class CanBasicFingers : public Base
{
    public:
    //Interface redefined by ofApp
    virtual void addTuioCursor(int32 id, float xpos,float ypos,float xspeed,float yspeed,float maccel){}
    virtual void updateTuioCursor(int32 id, float xpos,float ypos,float xspeed,float yspeed,float maccel){}
    virtual void removeTuioCursor(int32 id){}

    //processing events callbacks
    TCallBack(CanBasicFingers,event_finger_remove);
    TEventHandler(event_finger_remove)
    {
        TeventBasicFingersRemoveFinger * e = static_cast<TeventBasicFingersRemoveFinger *>(evt);
        removeTuioCursor(e->s_id);
    }
    TCallBack(CanBasicFingers,event_finger_new);
    TEventHandler(event_finger_new)
    {
        TeventBasicFingersNewFinger * e = static_cast<TeventBasicFingersNewFinger *>(evt);
        addTuioCursor(e->s_id,e->xpos, e->ypos, e->xspeed, e->yspeed, e->maccel);
    }
    TCallBack(CanBasicFingers,event_finger_move);
    TEventHandler(event_finger_move)
    {
        TeventBasicFingersMoveFinger * e = static_cast<TeventBasicFingersMoveFinger *>(evt);
        updateTuioCursor(e->s_id,e->xpos, e->ypos, e->xspeed, e->yspeed, e->maccel);
    }

    //registering
    CanBasicFingers()
    {
        TRegistraCallback(event_finger_remove);
        TRegistraCallback(event_finger_new);
        TRegistraCallback(event_finger_move);
        registerMeToInputGestureManager(new InputGestureBasicFingers());
    }

    //allways needed
    eventprocessorsType & getEP()
    {
        return Base::getEP();
    }
};

} // namespace tuio
#endif
