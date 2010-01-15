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

#ifndef INPUTGESTUREDIRECTOBJECTS_H_INCLUDED
#define INPUTGESTUREDIRECTOBJECTS_H_INCLUDED

#include "InputGestureBasicObjects.h"
#include "TEvent.h"
#include <map>

using namespace osc;

namespace tuio
{


class DirectObject
{
    public:
    int32 s_id, f_id;
    float xpos, ypos, angle, xspeed, yspeed, rspeed, maccel, raccel;
};

// Events definitions

class TeventDirectObjectsRemoveObject : public TTEvent <TeventDirectObjectsRemoveObject>
{
    public:
    int32 s_id, f_id;
};

class TeventDirectObjectsNewObject : public TTEvent<TeventDirectObjectsNewObject>
{
    public:
    int32 s_id, f_id;
    DirectObject * dob;
};

class InputGestureDirectObjects : public CanBasicObjects < tuioApp <InputGesture> > {
    std::map<int32,DirectObject *> objects;
    InputGestureBasicObjects * basicobjects;
    public:
        InputGestureDirectObjects(){basicobjects = Singleton< InputGestureBasicObjects>::get();}
        virtual void ReceiveCall(const char * addr, osc::ReceivedMessageArgumentStream & argList);
        void addTuioObject(int32 id, int32 f_id ,float xpos,float ypos, float angle, float xspeed,float yspeed,float rspeed,float maccel, float raccel);
        void updateTuioObject(int32 id, int32 f_id ,float xpos,float ypos, float angle, float xspeed,float yspeed,float rspeed,float maccel, float raccel);
        void removeTuioObject(int32 id);
};

template <class Base>
class CanDirectObjects : public  Base
{
    public:
    //Interface redefined by ofApp
    virtual void newObject(int32 s_id, int32 f_id, DirectObject *){}
    virtual void removeObject(int32 s_id, int32 f_id){}

    //processing events callbacks
    TEventHandler(TeventDirectObjectsRemoveObject)
    {
        TeventDirectObjectsRemoveObject * e = static_cast<TeventDirectObjectsRemoveObject *>(evt);
        removeObject(e->s_id, e->f_id);
    }
    TEventHandler(TeventDirectObjectsNewObject)
    {
        TeventDirectObjectsNewObject * e = static_cast<TeventDirectObjectsNewObject *>(evt);
        newObject(e->s_id,e->f_id, e->dob);
    }

    //registering
    CanDirectObjects()
    {
        TRegistraCallback(CanDirectObjects,TeventDirectObjectsRemoveObject);
        TRegistraCallback(CanDirectObjects,TeventDirectObjectsNewObject);
        registerMeToInputGestureManager(Singleton<InputGestureDirectObjects>::get());
    }

    //allways needed
    eventprocessorsType & getEP()
    {
        return Base::getEP();
    }
};


}
#endif // INPUTGESTUREDIRECTOBJECTS_H_INCLUDED
