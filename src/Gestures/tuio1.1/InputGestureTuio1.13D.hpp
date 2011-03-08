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
#include "InputGestureOsc.hpp"
#include "OscTools.hpp"


class InputGestureTuio113D : public Singleton<InputGestureTuio113D> {
    

    public:
    struct addTuioCursor3DArgs:     public EventArgs {int id; float xpos;float ypos;float zpos; float xspeed;float yspeed;float zspeed;float maccel;};
    struct updateTuioCursor3DArgs:  public EventArgs {int id; float xpos;float ypos;float zpos; float xspeed;float yspeed;float zspeed;float maccel;};
    struct removeTuioCursor3DArgs:  public EventArgs {int id;};
    struct addTuioObject3DArgs:     public EventArgs {int id; int f_id ;float xpos;float ypos; float zpos; float aangle; float bangle; float cangle; float xspeed;float yspeed; float zspeed; float aspeed; float bspeed; float cspeed; float maccel; float raccel;};
    struct updateTuioObject3DArgs:  public EventArgs {int id; int f_id ;float xpos;float ypos; float zpos; float aangle; float bangle; float cangle; float xspeed;float yspeed; float zspeed; float aspeed; float bspeed; float cspeed; float maccel; float raccel;};
    struct removeTuioObject3DArgs:  public EventArgs {int id;};
    
    ofEvent<addTuioCursor3DArgs>    addTuioCursor3D;
    ofEvent<updateTuioCursor3DArgs> updateTuioCursor3D;
    ofEvent<removeTuioCursor3DArgs> removeTuioCursor3D;
    ofEvent<addTuioObject3DArgs>    addTuioObject3D;
    ofEvent<updateTuioObject3DArgs> updateTuioObject3D;
    ofEvent<removeTuioObject3DArgs> removeTuioObject3D;

    std::set<int> c_s_ids;
    std::set<int> o_s_ids;


        InputGestureTuio113D()
        {
            ofAddListener(InputGestureOSC::Instance().EventNewOScMessage,this,&InputGestureTuio113D::ReceiveCall);
        }
        virtual ~InputGestureTuio113D()
        {
            ofRemoveListener(InputGestureOSC::Instance().EventNewOScMessage,this,&InputGestureTuio113D::ReceiveCall);
        }
        void ReceiveCall(InputGestureOSC::EventNewOScMessageArgs & args);
        void tuio3Dcur(OscOptionalUnpacker & argList);
        void tuio3Dobj(OscOptionalUnpacker & argList);

};

/*
template <class Base>
class CanTuio113D : public Base
{
    public:
    //Interface redefined by ofApp

    virtual void addTuioCursor3D(int id, float xpos,float ypos,float zpos, float xspeed,float yspeed,float zspeed,float maccel){}
    virtual void updateTuioCursor3D(int id, float xpos,float ypos,float zpos, float xspeed,float yspeed,float zspeed,float maccel){}
    virtual void removeTuioCursor3D(int id){}

    virtual void addTuioObject3D(int id, int f_id ,float xpos,float ypos, float zpos, float aangle, float bangle, float cangle, float xspeed,float yspeed, float zspeed, float aspeed, float bspeed, float cspeed, float maccel, float raccel){}
    virtual void updateTuioObject3D(int id, int f_id ,float xpos,float ypos, float zpos, float aangle, float bangle, float cangle, float xspeed,float yspeed, float zspeed, float aspeed, float bspeed, float cspeed, float maccel, float raccel){}
    virtual void removeTuioObject3D(int id){}

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
*/



#endif // INPUTGESTURETUIO1_13D_H_INCLUDED
