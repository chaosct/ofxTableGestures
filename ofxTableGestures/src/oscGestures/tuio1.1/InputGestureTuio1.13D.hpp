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

#ifndef INPUTGESTURETUIO1_13D_H_INCLUDED
#define INPUTGESTURETUIO1_13D_H_INCLUDED



#include <set>
#include "tuio1.1/InputGestureTuio1.1fseq.hpp"
using osc::int32;

namespace tuio {

///2.5D Events

class TeventTuio11RemoveFinger3D : public TTEvent<TeventTuio11RemoveFinger3D>
{
    public:
    int32 s_id;
};

class TeventTuio11NewFinger3D : public TTEvent< TeventTuio11NewFinger3D>
{
    public:
    int32 s_id;
    float xpos, ypos, zpos, xspeed, yspeed, zspeed, maccel;
};

class TeventTuio11MoveFinger3D : public TTEvent<TeventTuio11MoveFinger3D>
{
    public:
    int32 s_id;
    float xpos, ypos, zpos, xspeed, yspeed, zspeed, maccel;
};

class TeventTuio11RemoveObject3D : public TTEvent< TeventTuio11RemoveObject3D >
{
    public:
    int32 s_id;
};

class TeventTuio11NewObject3D : public TTEvent<TeventTuio11NewObject3D>
{
    public:
    int32 s_id, f_id;
    float xpos, ypos, zpos, aangle, bangle, cangle , xspeed, yspeed, zspeed, aspeed,bspeed,cspeed, maccel, raccel;
};

class TeventTuio11MoveObject3D : public TTEvent <TeventTuio11MoveObject3D>
{
    public:
    int32 s_id, f_id;
    float xpos, ypos, zpos, aangle, bangle, cangle , xspeed, yspeed, zspeed, aspeed,bspeed,cspeed, maccel, raccel;
};


class InputGestureTuio113D : public CanTuio11ValidBundle< CompositeGesture > {
    std::set<int32> c_s_ids;
    std::set<int32> o_s_ids;
    bool valid;
    public:
        InputGestureTuio113D(){}
        void ReceiveCall(const char * addr, osc::ReceivedMessageArgumentStream & argList);
        void tuio3Dcur(osc::ReceivedMessageArgumentStream & argList);
        void tuio3Dobj(osc::ReceivedMessageArgumentStream & argList);
        void isvalid(bool v){valid = v;}
};


template <class Base>
class CanTuio113D : public Base
{
    public:
    //Interface redefined by ofApp
    ///2.5D functions

    virtual void addTuioCursor3D(int32 id, float xpos,float ypos,float zpos, float xspeed,float yspeed,float zspeed,float maccel){}
    virtual void updateTuioCursor3D(int32 id, float xpos,float ypos,float zpos, float xspeed,float yspeed,float zspeed,float maccel){}
    virtual void removeTuioCursor3D(int32 id){}

    virtual void addTuioObject3D(int32 id, int32 f_id ,float xpos,float ypos, float zpos, float aangle, float bangle, float cangle, float xspeed,float yspeed, float zspeed, float aspeed, float bspeed, float cspeed, float maccel, float raccel){}
    virtual void updateTuioObject3D(int32 id, int32 f_id ,float xpos,float ypos, float zpos, float aangle, float bangle, float cangle, float xspeed,float yspeed, float zspeed, float aspeed, float bspeed, float cspeed, float maccel, float raccel){}
    virtual void removeTuioObject3D(int32 id){}

    ////2.5D Handlers

    TEventHandler(TeventTuio11RemoveFinger3D)
    {
        TeventTuio11RemoveFinger3D * e = static_cast<TeventTuio11RemoveFinger3D *>(evt);
        removeTuioCursor3D(e->s_id);
    }

    TEventHandler(TeventTuio11NewFinger3D)
    {
        TeventTuio11NewFinger3D * e = static_cast<TeventTuio11NewFinger3D *>(evt);
        addTuioCursor3D(e->s_id,e->xpos, e->ypos, e->zpos, e->xspeed, e->yspeed, e->zspeed, e->maccel);
    }

    TEventHandler(TeventTuio11MoveFinger3D)
    {
        TeventTuio11MoveFinger3D * e = static_cast<TeventTuio11MoveFinger3D *>(evt);
        updateTuioCursor3D(e->s_id,e->xpos, e->ypos, e->zpos, e->xspeed, e->yspeed, e->zspeed, e->maccel);
    }

       TEventHandler(TeventTuio11RemoveObject3D)
    {
        TeventTuio11RemoveObject3D * e = static_cast<TeventTuio11RemoveObject3D *>(evt);
        removeTuioObject3D(e->s_id);
    }

    TEventHandler(TeventTuio11NewObject3D)
    {
        TeventTuio11NewObject3D * e = static_cast<TeventTuio11NewObject3D *>(evt);
        addTuioObject3D(e->s_id, e->f_id, e->xpos, e->ypos, e->zpos, e->aangle, e->bangle, e->cangle, e->xspeed, e->yspeed, e->zspeed, e->aspeed, e->bspeed, e->cspeed, e->maccel, e->raccel);
    }

    TEventHandler(TeventTuio11MoveObject3D)
    {
        TeventTuio11MoveObject3D * e = static_cast<TeventTuio11MoveObject3D *>(evt);
        updateTuioObject3D(e->s_id, e->f_id, e->xpos, e->ypos, e->zpos, e->aangle, e->bangle, e->cangle, e->xspeed, e->yspeed, e->zspeed, e->aspeed, e->bspeed, e->cspeed, e->maccel, e->raccel);
    }


    //registering
    void Register(Area * a)
    {
        Base::Register(a);
        ///2.5D Events

        TRegistraCallback(CanTuio113D,TeventTuio11RemoveFinger3D);
        TRegistraCallback(CanTuio113D,TeventTuio11NewFinger3D);
        TRegistraCallback(CanTuio113D,TeventTuio11MoveFinger3D);
        TRegistraCallback(CanTuio113D,TeventTuio11RemoveObject3D);
        TRegistraCallback(CanTuio113D,TeventTuio11NewObject3D);
        TRegistraCallback(CanTuio113D,TeventTuio11MoveObject3D);
        Base::registerInputGesture(Singleton<InputGestureTuio113D>::get());
    }
};

}


#endif // INPUTGESTURETUIO1_13D_H_INCLUDED
