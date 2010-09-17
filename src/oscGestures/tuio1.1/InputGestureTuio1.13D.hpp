/*

    ofxTableGestures (formerly OF-TangibleFramework)
    Developed for Taller de Sistemes Interactius I
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
#include "InputGestureTuio1.1fseq.hpp"
using osc::int32;

namespace tuio {

SimpleDeclareEvent(CanTuio113D,addTuioCursor3D,int32,float,float,float,float,float,float,float);
SimpleDeclareEvent(CanTuio113D,updateTuioCursor3D,int32,float,float,float,float,float,float,float);
SimpleDeclareEvent(CanTuio113D,removeTuioCursor3D,int32);

SimpleDeclareEvent(CanTuio113D,addTuioObject3D,int32,int32,float,float,float,float,float,float,float,float,float,float,float,float,float,float);
SimpleDeclareEvent(CanTuio113D,updateTuioObject3D,int32,int32,float,float,float,float,float,float,float,float,float,float,float,float,float,float);
SimpleDeclareEvent(CanTuio113D,removeTuioObject3D,int32);

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

    virtual void addTuioCursor3D(int32 id, float xpos,float ypos,float zpos, float xspeed,float yspeed,float zspeed,float maccel){}
    virtual void updateTuioCursor3D(int32 id, float xpos,float ypos,float zpos, float xspeed,float yspeed,float zspeed,float maccel){}
    virtual void removeTuioCursor3D(int32 id){}

    virtual void addTuioObject3D(int32 id, int32 f_id ,float xpos,float ypos, float zpos, float aangle, float bangle, float cangle, float xspeed,float yspeed, float zspeed, float aspeed, float bspeed, float cspeed, float maccel, float raccel){}
    virtual void updateTuioObject3D(int32 id, int32 f_id ,float xpos,float ypos, float zpos, float aangle, float bangle, float cangle, float xspeed,float yspeed, float zspeed, float aspeed, float bspeed, float cspeed, float maccel, float raccel){}
    virtual void removeTuioObject3D(int32 id){}

    //registering
    void Register(Area * a)
    {
        Base::Register(a);

        SimpleRegisterEvent(CanTuio113D,addTuioCursor3D);
        SimpleRegisterEvent(CanTuio113D,updateTuioCursor3D);
        SimpleRegisterEvent(CanTuio113D,removeTuioCursor3D);

        SimpleRegisterEvent(CanTuio113D,addTuioObject3D);
        SimpleRegisterEvent(CanTuio113D,updateTuioObject3D);
        SimpleRegisterEvent(CanTuio113D,removeTuioObject3D);

        Base::template registerIG<InputGestureTuio113D>();
    }
};

}


#endif // INPUTGESTURETUIO1_13D_H_INCLUDED
