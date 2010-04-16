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

#ifndef INPUTGESTURETUIO1_12_5D_H_INCLUDED
#define INPUTGESTURETUIO1_12_5D_H_INCLUDED



#include <set>
#include "tuio1.1/InputGestureTuio1.1fseq.hpp"
using osc::int32;

namespace tuio {

///2.5D Events

class TeventTuio11RemoveFinger25D : public TTEvent<TeventTuio11RemoveFinger25D>
{
    public:
    int32 s_id;
};

class TeventTuio11NewFinger25D : public TTEvent< TeventTuio11NewFinger25D>
{
    public:
    int32 s_id;
    float xpos, ypos, zpos, xspeed, yspeed, zspeed, maccel;
};

class TeventTuio11MoveFinger25D : public TTEvent<TeventTuio11MoveFinger25D>
{
    public:
    int32 s_id;
    float xpos, ypos, zpos, xspeed, yspeed, zspeed, maccel;
};

class TeventTuio11RemoveObject25D : public TTEvent< TeventTuio11RemoveObject25D >
{
    public:
    int32 s_id;
};

class TeventTuio11NewObject25D : public TTEvent<TeventTuio11NewObject25D>
{
    public:
    int32 s_id, f_id;
    float xpos, ypos, zpos, angle, xspeed, yspeed, zspeed, rspeed, maccel, raccel;
};

class TeventTuio11MoveObject25D : public TTEvent <TeventTuio11MoveObject25D>
{
    public:
    int32 s_id, f_id;
    float xpos, ypos, zpos, angle, xspeed, yspeed, zspeed, rspeed, maccel, raccel;
};

class TeventTuio11RemoveBlob25D : public TTEvent< TeventTuio11RemoveBlob25D >
{
    public:
    int32 s_id;
};

class TeventTuio11NewBlob25D : public TTEvent<TeventTuio11NewBlob25D>
{
    public:
    int32 s_id;
    float xpos, ypos, zpos, angle, width, height, area, xspeed, yspeed, zspeed, rspeed, maccel, raccel;
};

class TeventTuio11MoveBlob25D : public TTEvent <TeventTuio11MoveBlob25D>
{
    public:
    int32 s_id;
    float xpos, ypos, zpos, angle, width, height, area, xspeed, yspeed, zspeed, rspeed, maccel, raccel;
};

class InputGestureTuio1125D : public CanTuio11ValidBundle< CompositeGesture > {
    std::set<int32> c_s_ids;
    std::set<int32> o_s_ids;
    std::set<int32> b_s_ids;
    bool valid;
    public:
        InputGestureTuio1125D(){}
        void ReceiveCall(const char * addr, osc::ReceivedMessageArgumentStream & argList);
        void tuio25Dcur(osc::ReceivedMessageArgumentStream & argList);
        void tuio25Dobj(osc::ReceivedMessageArgumentStream & argList);
        void tuio25Dblb(osc::ReceivedMessageArgumentStream & argList);
        void isvalid(bool v){valid = v;}
};


template <class Base>
class CanTuio1125D : public Base
{
    public:
    //Interface redefined by ofApp
    ///2.5D functions

    virtual void addTuioCursor25D(int32 id, float xpos,float ypos,float zpos, float xspeed,float yspeed,float zspeed,float maccel){}
    virtual void updateTuioCursor25D(int32 id, float xpos,float ypos,float zpos, float xspeed,float yspeed,float zspeed,float maccel){}
    virtual void removeTuioCursor25D(int32 id){}

    virtual void addTuioObject25D(int32 id, int32 f_id ,float xpos,float ypos, float zpos, float angle, float xspeed,float yspeed, float zspeed, float rspeed,float maccel, float raccel){}
    virtual void updateTuioObject25D(int32 id, int32 f_id ,float xpos,float ypos, float zpos, float angle, float xspeed,float yspeed, float zspeed, float rspeed,float maccel, float raccel){}
    virtual void removeTuioObject25D(int32 id){}

    virtual void addTuioBlob25D(int32 id,float xpos,float ypos, float zpos, float angle, float width, float height, float area, float xspeed,float yspeed, float zspeed, float rspeed,float maccel, float raccel){}
    virtual void updateTuioBlob25D(int32 id,float xpos,float ypos, float zpos, float angle, float width, float height, float area, float xspeed,float yspeed, float zspeed, float rspeed,float maccel, float raccel){}
    virtual void removeTuioBlob25D(int32 id){}

    ////2.5D Handlers

    TEventHandler(TeventTuio11RemoveFinger25D)
    {
        TeventTuio11RemoveFinger25D * e = static_cast<TeventTuio11RemoveFinger25D *>(evt);
        removeTuioCursor25D(e->s_id);
    }

    TEventHandler(TeventTuio11NewFinger25D)
    {
        TeventTuio11NewFinger25D * e = static_cast<TeventTuio11NewFinger25D *>(evt);
        addTuioCursor25D(e->s_id,e->xpos, e->ypos, e->zpos, e->xspeed, e->yspeed, e->zspeed, e->maccel);
    }

    TEventHandler(TeventTuio11MoveFinger25D)
    {
        TeventTuio11MoveFinger25D * e = static_cast<TeventTuio11MoveFinger25D *>(evt);
        updateTuioCursor25D(e->s_id,e->xpos, e->ypos, e->zpos, e->xspeed, e->yspeed, e->zspeed, e->maccel);
    }

    TEventHandler(TeventTuio11RemoveObject25D)
    {
        TeventTuio11RemoveObject25D * e = static_cast<TeventTuio11RemoveObject25D *>(evt);
        removeTuioObject25D(e->s_id);
    }

    TEventHandler(TeventTuio11NewObject25D)
    {
        TeventTuio11NewObject25D * e = static_cast<TeventTuio11NewObject25D *>(evt);
        addTuioObject25D(e->s_id, e->f_id, e->xpos, e->ypos, e->zpos, e->angle, e->xspeed, e->yspeed, e->zspeed, e->rspeed, e->maccel, e->raccel);
    }

    TEventHandler(TeventTuio11MoveObject25D)
    {
        TeventTuio11MoveObject25D * e = static_cast<TeventTuio11MoveObject25D *>(evt);
        updateTuioObject25D(e->s_id, e->f_id, e->xpos, e->ypos, e->zpos, e->angle, e->xspeed, e->yspeed, e->zspeed, e->rspeed, e->maccel, e->raccel);
    }

    TEventHandler(TeventTuio11RemoveBlob25D)
    {
        TeventTuio11RemoveBlob25D * e = static_cast<TeventTuio11RemoveBlob25D *>(evt);
        removeTuioBlob25D(e->s_id);
    }

    TEventHandler(TeventTuio11NewBlob25D)
    {
        TeventTuio11NewBlob25D * e = static_cast<TeventTuio11NewBlob25D *>(evt);
        addTuioBlob25D(e->s_id, e->xpos, e->ypos, e->zpos, e->angle, e->width, e->height, e->area, e->xspeed, e->yspeed, e->zspeed, e->rspeed, e->maccel, e->raccel);
    }

    TEventHandler(TeventTuio11MoveBlob25D)
    {
        TeventTuio11MoveBlob25D * e = static_cast<TeventTuio11MoveBlob25D *>(evt);
        updateTuioBlob25D(e->s_id, e->xpos, e->ypos, e->zpos, e->angle, e->width, e->height, e->area, e->xspeed, e->yspeed, e->zspeed, e->rspeed, e->maccel, e->raccel);
    }

    //registering
    CanTuio1125D()
    {
        ///2.5D Events

        TRegistraCallback(CanTuio1125D,TeventTuio11RemoveFinger25D);
        TRegistraCallback(CanTuio1125D,TeventTuio11NewFinger25D);
        TRegistraCallback(CanTuio1125D,TeventTuio11MoveFinger25D);

        TRegistraCallback(CanTuio1125D,TeventTuio11RemoveObject25D);
        TRegistraCallback(CanTuio1125D,TeventTuio11NewObject25D);
        TRegistraCallback(CanTuio1125D,TeventTuio11MoveObject25D);

        TRegistraCallback(CanTuio1125D,TeventTuio11RemoveBlob25D);
        TRegistraCallback(CanTuio1125D,TeventTuio11NewBlob25D);
        TRegistraCallback(CanTuio1125D,TeventTuio11MoveBlob25D);

        Base::registerInputGesture(Singleton<InputGestureTuio1125D>::get());
    }
};

}


#endif // INPUTGESTURETUIO1_12_5D_H_INCLUDED
