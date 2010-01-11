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

#ifndef TUIO_INPUTGESTUREBASICOBJECTS_H
#define TUIO_INPUTGESTUREBASICOBJECTS_H

#include "osc/OscReceivedElements.h"
#include "InputGesture.h"
#include <set>
#include "TEvent.h"
#include "tuioApp.h"

using namespace osc;

namespace tuio {

class TeventBasicObjectsRemoveObject : public TEvent
{
    public:
    TeventBasicObjectsRemoveObject():TEvent(event_object_remove){}
    int32 s_id;
};

class TeventBasicObjectsNewObject : public TEvent
{
    public:
    TeventBasicObjectsNewObject():TEvent(event_object_new){}
    int32 s_id, f_id;
    float xpos, ypos, angle, xspeed, yspeed, rspeed, maccel, raccel;
};

class TeventBasicObjectsMoveObject : public TEvent
{
    public:
    TeventBasicObjectsMoveObject():TEvent(event_object_move){}
    int32 s_id, f_id;
    float xpos, ypos, angle, xspeed, yspeed, rspeed, maccel, raccel;
};


class InputGestureBasicObjects : public InputGesture {
    std::set<int32> s_ids;
    int32 currentFrame, lastFrame;
    public:
        InputGestureBasicObjects():currentFrame(0),lastFrame(0){}
        virtual void ReceiveCall(const char * addr, osc::ReceivedMessageArgumentStream & argList);
};

template <class Base>
class CanBasicObjects : public Base
{
    public:
    //Interface redefined by ofApp
    virtual void addTuioObject(int32 id, int32 f_id ,float xpos,float ypos, float angle, float xspeed,float yspeed,float rspeed,float maccel, float raccel){}
    virtual void updateTuioObject(int32 id, int32 f_id ,float xpos,float ypos, float angle, float xspeed,float yspeed,float rspeed,float maccel, float raccel){}
    virtual void removeTuioObject(int32 id){}

    //processing events callbacks

    TEventHandler(event_object_remove)
    {
        TeventBasicObjectsRemoveObject * e = static_cast<TeventBasicObjectsRemoveObject *>(evt);
        removeTuioObject(e->s_id);
    }

    TEventHandler(event_object_new)
    {
        TeventBasicObjectsNewObject * e = static_cast<TeventBasicObjectsNewObject *>(evt);
        addTuioObject(e->s_id, e->f_id, e->xpos, e->ypos, e->angle, e->xspeed, e->yspeed, e->rspeed, e->maccel, e->raccel);
    }

    TEventHandler(event_object_move)
    {
        TeventBasicObjectsMoveObject * e = static_cast<TeventBasicObjectsMoveObject *>(evt);
        updateTuioObject(e->s_id, e->f_id, e->xpos, e->ypos, e->angle, e->xspeed, e->yspeed, e->rspeed, e->maccel, e->raccel);
    }

    //registering
    CanBasicObjects()
    {
        TRegistraCallback(CanBasicObjects,event_object_remove);
        TRegistraCallback(CanBasicObjects,event_object_new);
        TRegistraCallback(CanBasicObjects,event_object_move);
        registerMeToInputGestureManager(Singleton<InputGestureBasicObjects>::get());
    }

    //allways needed
    eventprocessorsType & getEP()
    {
        return Base::getEP();
    }
};

} // namespace tuio
#endif
