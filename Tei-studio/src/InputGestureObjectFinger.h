/*

    OF-TangibleFramework . Framework for Tei-studio
    Universitat Pompeu Fabra

    Copyright (c) 2009 Daniel Gallardo Grassot <daniel.gallardo@upf.edu>

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

#ifndef INPUTGESTUREFINGEROBJECT_H_INCLUDED
#define INPUTGESTUREFINGEROBJECT_H_INCLUDED


#include "TEvent.h"

#include "InputGestureDirectFingers.h"
#include "InputGestureBasicFingers.h"
#include "InputGestureDirectObjects.h"
#include "InputGestureTap.h"
#include <map>
#include <list>

///Physical radius of an average fiducial size
#define FIGURE_OFFSET       0.035f
///gesture bound
#define GESTURE_DISTANCE    FIGURE_OFFSET+0.05f

namespace tuio
{

class objectfinger{
    public:
    /////////////Vars//////////////////////////////
    /// stores data of the object
    DirectObject* object;
    /// stores finger data related with the object
    std::map<int32, DirectFinger*> fingers;
    /////////////Methods///////////////////////////
    ///constructor
    objectfinger(DirectObject* obj);
    ///distance object-finger
    float distance (DirectFinger* finger);
    ///distance object-(x,y)
    float distance (float x, float y);
    ///relates finger with the object
    void fingerAdd(DirectFinger* finger);
    ///removes finger
    void fingerRemove(int32 s_id);
    ///check if finger is related
    bool containsFinger(int32 id);
};

/// Events declare
/// TeventObjectFingerAdd -> reports an adition of a finger
class TeventObjectFingerAdd : public TTEvent <TeventObjectFingerAdd>{
public:
    DirectObject* object;
    DirectFinger* finger;
};

/// TeventObjectFingerUpdate -> reports an update of a finger
class TeventObjectFingerUpdate : public TTEvent <TeventObjectFingerUpdate>{
public:
    DirectObject* object;
    DirectFinger* finger;
};

/// TeventObjectFingerRelease -> reports a release of a finger
class TeventObjectFingerRelease : public TTEvent <TeventObjectFingerRelease>{
public:
    DirectObject* object;
    DirectFinger* finger;
};

/// TeventObjectFingerTap -> reports a 'Tap' gesture of a finger
class TeventObjectFingerTap : public TTEvent <TeventObjectFingerTap>{
public:
    DirectObject* object;
    float x,y;
};


class InputObjectFinger : public CanTap < CanBasicFingers < CanDirectFingers < CanDirectObjects < tuioApp <InputGesture> > > > >
{
    private:
        ///objects -> where all object related data wil be stored
        std::map<int32,objectfinger*> objects;
        ///orphan_fingers -> fingers not related with objects
        std::map<int32,DirectFinger*> orphan_fingers;
    ///Input gesture data
        ///basicfingers -> cursor input
        InputGestureBasicFingers * basicfingers;
        ///directfingers -> cursor input with encapsulated data
        InputGestureDirectFingers * directfingers;
        ///directobjects -> object input with encapsulated fata
        InputGestureDirectObjects * directobjects;
        ///inputTap -> tap input
        InputGestureTap *inputTap;
    public:
    ///Constructor
        ///Initializes the input data
        InputObjectFinger();
        ///Process all data fom each input gesture
        virtual void ReceiveCall(const char * addr, osc::ReceivedMessageArgumentStream & argList);
    ///FromCanDirectObjects:
        ///newObject: report a new instance of an object, data:
            ///s_id -> fiducial session identifyer
            ///f_if -> fiducial number
            ///obj -> encapsulation of position , angle and data related with position and angle
        virtual void newObject(int32 s_id, int32 f_id, DirectObject * obj);
        ///removeObject: removes an existing object, data:
            ///s_id -> fiducial session identifyer
            ///f_if -> fiducial number
        virtual void removeObject(int32 s_id, int32 f_id);
    ///FromCanDirectFingers
        ///newObject: report a new instance of a cursor, data:
            ///s_id -> cursor session identifyer
            ///dfi -> encapsulation of position and data related with position
        virtual void newCursor(int32 id, DirectFinger * dfi);
        ///newObject: reports remove cursor, data:
            ///s_id -> cursor session identifyer
        virtual void removeCursor(int32 id);
    /// from can basic fingers
        ///updateTuioCursor: reports a cursor update
        virtual void updateTuioCursor(int32 id, float xpos,float ypos,float xspeed,float yspeed,float maccel);
    ///From Tap
        ///tap -> reports a Tap
        virtual void tap(float x, float y);
};


template <class Base>
class CanObjectFinger : public  Base
{
public:
    //Interface redefined by ofApp
    virtual void objectFingerAdd(DirectObject* obj, DirectFinger* finger) {}
    virtual void objectFingerUpdate(DirectObject* obj, DirectFinger* finger) {}
    virtual void objectFingerRemove(DirectObject* obj, DirectFinger* finger) {}
    virtual void objectFingerTap(DirectObject* obj, float x, float y) {}

    //processing events callbacks
    TEventHandler(TeventObjectFingerAdd)
    {
        TeventObjectFingerAdd * e = static_cast<TeventObjectFingerAdd *>(evt);
        objectFingerAdd(e->object,e->finger);
    }
    TEventHandler(TeventObjectFingerUpdate)
    {
        TeventObjectFingerUpdate * e = static_cast<TeventObjectFingerUpdate *>(evt);
        objectFingerUpdate(e->object,e->finger);
    }
    TEventHandler(TeventObjectFingerRelease)
    {
        TeventObjectFingerRelease * e = static_cast<TeventObjectFingerRelease *>(evt);
        objectFingerRemove(e->object,e->finger);
    }
    TEventHandler(TeventObjectFingerTap)
    {
        TeventObjectFingerTap * e = static_cast<TeventObjectFingerTap *>(evt);
        objectFingerTap(e->object,e->x,e->y);
    }

    //registering
    CanObjectFinger()
    {
        TRegistraCallback(CanObjectFinger,TeventObjectFingerAdd);
        TRegistraCallback(CanObjectFinger,TeventObjectFingerUpdate);
        TRegistraCallback(CanObjectFinger,TeventObjectFingerRelease);
        TRegistraCallback(CanObjectFinger,TeventObjectFingerTap);
        registerMeToInputGestureManager(Singleton<InputObjectFinger>::get());
    }

};

}
#endif // INPUTGESTUREFINGEROBJECT_H_INCLUDED
