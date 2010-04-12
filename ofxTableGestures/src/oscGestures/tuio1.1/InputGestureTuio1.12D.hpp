#ifndef INPUTGESTURETUIO1_12D_H_INCLUDED
#define INPUTGESTURETUIO1_12D_H_INCLUDED


#include <set>
#include "tuio1.1/InputGestureTuio1.1fseq.hpp"
#include "GlobalConfig.hpp"

using osc::int32;

namespace tuio {

///2D Events

class TeventTuio11RemoveFinger2D : public TTEvent<TeventTuio11RemoveFinger2D>
{
    public:
    int32 s_id;
};

class TeventTuio11NewFinger2D : public TTEvent< TeventTuio11NewFinger2D>
{
    public:
    int32 s_id;
    float xpos, ypos, xspeed, yspeed, maccel;
};

class TeventTuio11MoveFinger2D : public TTEvent<TeventTuio11MoveFinger2D>
{
    public:
    int32 s_id;
    float xpos, ypos, xspeed, yspeed, maccel;
};

class TeventTuio11RemoveObject2D : public TTEvent< TeventTuio11RemoveObject2D >
{
    public:
    int32 s_id;
};

class TeventTuio11NewObject2D : public TTEvent<TeventTuio11NewObject2D>
{
    public:
    int32 s_id, f_id;
    float xpos, ypos, angle, xspeed, yspeed, rspeed, maccel, raccel;
};

class TeventTuio11MoveObject2D : public TTEvent <TeventTuio11MoveObject2D>
{
    public:
    int32 s_id, f_id;
    float xpos, ypos, angle, xspeed, yspeed, rspeed, maccel, raccel;
};

class TeventTuio11RemoveBlob2D : public TTEvent <TeventTuio11RemoveBlob2D>
{
    public:
    int32 s_id;
};

class TeventTuio11NewBlob2D : public TTEvent <TeventTuio11NewBlob2D>
{
  public:
  int32 s_id;
  float xpos, ypos, angle, width, height, area, xspeed, yspeed, rspeed, maccel, raccel;
};

class TeventTuio11MoveBlob2D : public TTEvent <TeventTuio11MoveBlob2D>
{
  public:
  int32 s_id;
  float xpos, ypos, angle, width, height, area, xspeed, yspeed, rspeed, maccel, raccel;
};

class InputGestureTuio112D : public CanTuio11ValidBundle< CompositeGesture > {
    std::set<int32> c_s_ids;
    std::set<int32> o_s_ids;
    std::set<int32> b_s_ids;
    bool valid;
    int & checkCursorLimits;
    int & checkObjectLimits;
    public:
        InputGestureTuio112D():
        checkCursorLimits(GlobalConfig::getRef("TUIO112D:CUR:CheckLimits",0)),
        checkObjectLimits(GlobalConfig::getRef("TUIO112D:OBJ:CheckLimits",0))
        {}
        void ReceiveCall(const char * addr, osc::ReceivedMessageArgumentStream & argList);
        void tuio2Dcur(osc::ReceivedMessageArgumentStream & argList);
        void tuio2Dobj(osc::ReceivedMessageArgumentStream & argList);
        void tuio2Dblb(osc::ReceivedMessageArgumentStream & argList);
        void isvalid(bool v){valid = v;}
};


template <class Base>
class CanTuio112D : public Base
{
    public:
    //Interface redefined by ofApp
    ///2D functions
    virtual void addTuioCursor2D(int32 id, float xpos,float ypos,float xspeed,float yspeed,float maccel){}
    virtual void updateTuioCursor2D(int32 id, float xpos,float ypos,float xspeed,float yspeed,float maccel){}
    virtual void removeTuioCursor2D(int32 id){}

    virtual void addTuioObject2D(int32 id, int32 f_id ,float xpos,float ypos, float angle, float xspeed,float yspeed,float rspeed,float maccel, float raccel){}
    virtual void updateTuioObject2D(int32 id, int32 f_id ,float xpos,float ypos, float angle, float xspeed,float yspeed,float rspeed,float maccel, float raccel){}
    virtual void removeTuioObject2D(int32 id){}

    virtual void addTuioBlob2D(int32 id,float xpos,float ypos, float angle, float width, float height, float area, float xspeed,float yspeed,float rspeed,float maccel, float raccel){}
    virtual void updateTuioBlob2D(int32 id,float xpos,float ypos, float angle, float width, float height, float area, float xspeed,float yspeed,float rspeed,float maccel, float raccel){}
    virtual void removeTuioBlob2D(int32 id){}

    ///2D Handlers

    TEventHandler(TeventTuio11RemoveFinger2D)
    {
        TeventTuio11RemoveFinger2D * e = static_cast<TeventTuio11RemoveFinger2D *>(evt);
        removeTuioCursor2D(e->s_id);
    }

    TEventHandler(TeventTuio11NewFinger2D)
    {
        TeventTuio11NewFinger2D * e = static_cast<TeventTuio11NewFinger2D *>(evt);
        addTuioCursor2D(e->s_id,e->xpos, e->ypos, e->xspeed, e->yspeed, e->maccel);
    }

    TEventHandler(TeventTuio11MoveFinger2D)
    {
        TeventTuio11MoveFinger2D * e = static_cast<TeventTuio11MoveFinger2D *>(evt);
        updateTuioCursor2D(e->s_id,e->xpos, e->ypos, e->xspeed, e->yspeed, e->maccel);
    }

    TEventHandler(TeventTuio11RemoveObject2D)
    {
        TeventTuio11RemoveObject2D * e = static_cast<TeventTuio11RemoveObject2D *>(evt);
        removeTuioObject2D(e->s_id);
    }

    TEventHandler(TeventTuio11NewObject2D)
    {
        TeventTuio11NewObject2D * e = static_cast<TeventTuio11NewObject2D *>(evt);
        addTuioObject2D(e->s_id, e->f_id, e->xpos, e->ypos, e->angle, e->xspeed, e->yspeed, e->rspeed, e->maccel, e->raccel);
    }

    TEventHandler(TeventTuio11MoveObject2D)
    {
        TeventTuio11MoveObject2D * e = static_cast<TeventTuio11MoveObject2D *>(evt);
        updateTuioObject2D(e->s_id, e->f_id, e->xpos, e->ypos, e->angle, e->xspeed, e->yspeed, e->rspeed, e->maccel, e->raccel);
    }

    TEventHandler(TeventTuio11RemoveBlob2D)
    {
        TeventTuio11RemoveBlob2D * e = static_cast<TeventTuio11RemoveBlob2D *>(evt);
        removeTuioBlob2D(e->s_id);
    }

    TEventHandler(TeventTuio11NewBlob2D)
    {
        TeventTuio11NewBlob2D * e = static_cast<TeventTuio11NewBlob2D *>(evt);
        addTuioBlob2D(e->s_id, e->xpos, e->ypos, e->angle, e->width, e->height, e->area, e->xspeed, e->yspeed, e->rspeed, e->maccel, e->raccel);
    }

    TEventHandler(TeventTuio11MoveBlob2D)
    {
        TeventTuio11MoveBlob2D * e = static_cast<TeventTuio11MoveBlob2D *>(evt);
        updateTuioBlob2D(e->s_id, e->xpos, e->ypos, e->angle, e->width, e->height, e->area, e->xspeed, e->yspeed, e->rspeed, e->maccel, e->raccel);
    }


    //registering
    CanTuio112D()
    {
        ///2D Events
        TRegistraCallback(CanTuio112D,TeventTuio11RemoveFinger2D);
        TRegistraCallback(CanTuio112D,TeventTuio11NewFinger2D);
        TRegistraCallback(CanTuio112D,TeventTuio11MoveFinger2D);

        TRegistraCallback(CanTuio112D,TeventTuio11RemoveObject2D);
        TRegistraCallback(CanTuio112D,TeventTuio11NewObject2D);
        TRegistraCallback(CanTuio112D,TeventTuio11MoveObject2D);

        TRegistraCallback(CanTuio112D,TeventTuio11RemoveBlob2D);
        TRegistraCallback(CanTuio112D,TeventTuio11NewBlob2D);
        TRegistraCallback(CanTuio112D,TeventTuio11MoveBlob2D);

        Base::registerInputGesture(Singleton<InputGestureTuio112D>::get());
    }
};

}

#endif // INPUTGESTURETUIO1_12D_H_INCLUDED
