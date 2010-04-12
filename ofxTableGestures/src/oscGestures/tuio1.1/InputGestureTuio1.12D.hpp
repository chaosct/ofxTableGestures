#ifndef INPUTGESTURETUIO1_12D_H_INCLUDED
#define INPUTGESTURETUIO1_12D_H_INCLUDED


#include <set>
#include "tuio1.1/InputGestureTuio1.1fseq.hpp"
#include "GlobalConfig.hpp"

using osc::int32;

namespace tuio {

///2D Events

SimpleDeclareEvent(CanTuio112D,removeTuioCursor2D,int32);
SimpleDeclareEvent(CanTuio112D,addTuioCursor2D,int32,float,float, float, float, float );
SimpleDeclareEvent(CanTuio112D,updateTuioCursor2D,int32,float,float, float, float, float );

SimpleDeclareEvent(CanTuio112D,removeTuioObject2D,int32);
SimpleDeclareEvent(CanTuio112D,updateTuioObject2D,int32, int32 ,float ,float , float , float ,float ,float ,float , float );
SimpleDeclareEvent(CanTuio112D,addTuioObject2D,int32, int32 ,float ,float , float , float ,float ,float ,float , float );

SimpleDeclareEvent(CanTuio112D,removeTuioBlob2D,int32);
SimpleDeclareEvent(CanTuio112D,updateTuioBlob2D,int32, float ,float , float , float , float , float , float ,float ,float ,float , float );
SimpleDeclareEvent(CanTuio112D,addTuioBlob2D,int32, float ,float , float , float , float , float , float ,float ,float ,float , float );

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

    //registering
    CanTuio112D()
    {
        ///2D Events

        SimpleRegisterEvent(CanTuio112D,removeTuioCursor2D);
        SimpleRegisterEvent(CanTuio112D,addTuioCursor2D);
        SimpleRegisterEvent(CanTuio112D,updateTuioCursor2D);

        SimpleRegisterEvent(CanTuio112D,addTuioObject2D);
        SimpleRegisterEvent(CanTuio112D,updateTuioObject2D);
        SimpleRegisterEvent(CanTuio112D,removeTuioObject2D);

        SimpleRegisterEvent(CanTuio112D,addTuioBlob2D);
        SimpleRegisterEvent(CanTuio112D,updateTuioBlob2D);
        SimpleRegisterEvent(CanTuio112D,removeTuioBlob2D);

        Base::template registerIG<InputGestureTuio112D>();
    }
};

}

#endif // INPUTGESTURETUIO1_12D_H_INCLUDED
