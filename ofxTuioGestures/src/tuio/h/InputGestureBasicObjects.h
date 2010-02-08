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

#ifndef TUIO_INPUTGESTUREBASICOBJECTS_H
#define TUIO_INPUTGESTUREBASICOBJECTS_H

#include "OscReceivedElements.h"
#include "InputGesture.h"
#include <set>
#include "TEvent.h"
#include "tuioApp.h"
#include "InputGestureTuio1.1.h"

using namespace osc;

namespace tuio
{

class TeventBasicObjectsRemoveObject : public TTEvent< TeventBasicObjectsRemoveObject >
{
public:
    int32 s_id;
};

class TeventBasicObjectsNewObject : public TTEvent<TeventBasicObjectsNewObject>
{
public:
    int32 s_id, f_id;
    float xpos, ypos, angle, xspeed, yspeed, rspeed, maccel, raccel;
};

class TeventBasicObjectsMoveObject : public TTEvent <TeventBasicObjectsMoveObject>
{
public:
    int32 s_id, f_id;
    float xpos, ypos, angle, xspeed, yspeed, rspeed, maccel, raccel;
};


class InputGestureBasicObjects : public CanTuio112D < CompositeGesture >
{
public:
    InputGestureBasicObjects() {}
    void addTuioObject2D(int32 id, int32 f_id ,float xpos,float ypos, float angle, float xspeed,float yspeed,float rspeed,float maccel, float raccel)
    {
        TeventBasicObjectsNewObject * e = new TeventBasicObjectsNewObject();
        e->s_id = id;
        e->f_id = f_id;
        e->xpos = xpos;
        e->ypos = ypos;
        e->angle = angle;
        e->xspeed = xspeed;
        e->yspeed = yspeed;
        e->rspeed = rspeed;
        e->maccel = maccel;
        e->raccel = raccel;
        events.push_back(e);
    }
    void updateTuioObject2D(int32 id, int32 f_id ,float xpos,float ypos, float angle, float xspeed,float yspeed,float rspeed,float maccel, float raccel)
    {
        TeventBasicObjectsMoveObject * e = new TeventBasicObjectsMoveObject();
        e->s_id = id;
        e->f_id = f_id;
        e->xpos = xpos;
        e->ypos = ypos;
        e->angle = angle;
        e->xspeed = xspeed;
        e->yspeed = yspeed;
        e->rspeed = rspeed;
        e->maccel = maccel;
        e->raccel = raccel;
        events.push_back(e);
    }
    void removeTuioObject2D(int32 id)
    {
        TeventBasicObjectsRemoveObject * e = new TeventBasicObjectsRemoveObject();
        e->s_id = id;
        events.push_back(e);
    }
};

template <class Base>
class CanBasicObjects : public Base
{
public:
    //Interface redefined by ofApp
    virtual void addTuioObject(int32 id, int32 f_id ,float xpos,float ypos, float angle, float xspeed,float yspeed,float rspeed,float maccel, float raccel) {}
    virtual void updateTuioObject(int32 id, int32 f_id ,float xpos,float ypos, float angle, float xspeed,float yspeed,float rspeed,float maccel, float raccel) {}
    virtual void removeTuioObject(int32 id) {}

    //processing events callbacks

    TEventHandler(TeventBasicObjectsRemoveObject)
    {
        TeventBasicObjectsRemoveObject * e = static_cast<TeventBasicObjectsRemoveObject *>(evt);
        removeTuioObject(e->s_id);
    }

    TEventHandler(TeventBasicObjectsNewObject)
    {
        TeventBasicObjectsNewObject * e = static_cast<TeventBasicObjectsNewObject *>(evt);
        addTuioObject(e->s_id, e->f_id, e->xpos, e->ypos, e->angle, e->xspeed, e->yspeed, e->rspeed, e->maccel, e->raccel);
    }

    TEventHandler(TeventBasicObjectsMoveObject)
    {
        TeventBasicObjectsMoveObject * e = static_cast<TeventBasicObjectsMoveObject *>(evt);
        updateTuioObject(e->s_id, e->f_id, e->xpos, e->ypos, e->angle, e->xspeed, e->yspeed, e->rspeed, e->maccel, e->raccel);
    }

    //registering
    CanBasicObjects()
    {
        TRegistraCallback(CanBasicObjects,TeventBasicObjectsRemoveObject);
        TRegistraCallback(CanBasicObjects,TeventBasicObjectsNewObject);
        TRegistraCallback(CanBasicObjects,TeventBasicObjectsMoveObject);
        Base::registerInputGesture(Singleton<InputGestureBasicObjects>::get());
    }

};

} // namespace tuio
#endif
