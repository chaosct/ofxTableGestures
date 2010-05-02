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

SimpleDeclareEvent(CanTuio1125D,addTuioCursor25D,int32,float,float,float,float,float,float,float);
SimpleDeclareEvent(CanTuio1125D,updateTuioCursor25D,int32,float,float,float,float,float,float,float);
SimpleDeclareEvent(CanTuio1125D,removeTuioCursor25D,int32);

SimpleDeclareEvent(CanTuio1125D,addTuioObject25D,int32,int32,float,float,float,float,float,float,float,float,float,float);
SimpleDeclareEvent(CanTuio1125D,updateTuioObject25D,int32,int32,float,float,float,float,float,float,float,float,float,float);
SimpleDeclareEvent(CanTuio1125D,removeTuioObject25D,int32);

SimpleDeclareEvent(CanTuio1125D,addTuioBlob25D,int32,float,float,float,float,float,float,float,float,float,float,float,float,float);
SimpleDeclareEvent(CanTuio1125D,updateTuioBlob25D,int32,float,float,float,float,float,float,float,float,float,float,float,float,float);
SimpleDeclareEvent(CanTuio1125D,removeTuioBlob25D,int32);

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

    //registering
    void Register(Area * a)
    {
        Base::Register(a);
        ///2.5D Events

        SimpleRegisterEvent(CanTuio1125D,addTuioCursor25D);
        SimpleRegisterEvent(CanTuio1125D,addTuioObject25D);
        SimpleRegisterEvent(CanTuio1125D,addTuioBlob25D);

        SimpleRegisterEvent(CanTuio1125D,updateTuioCursor25D);
        SimpleRegisterEvent(CanTuio1125D,updateTuioObject25D);
        SimpleRegisterEvent(CanTuio1125D,updateTuioBlob25D);

        SimpleRegisterEvent(CanTuio1125D,removeTuioCursor25D);
        SimpleRegisterEvent(CanTuio1125D,removeTuioObject25D);
        SimpleRegisterEvent(CanTuio1125D,removeTuioBlob25D);

        Base::template registerIG<InputGestureTuio1125D>();
    }
};

}


#endif // INPUTGESTURETUIO1_12_5D_H_INCLUDED
