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

#ifndef INPUTGESTURETUIO1_12_5D_H_INCLUDED
#define INPUTGESTURETUIO1_12_5D_H_INCLUDED



#include <set>
#include "InputGestureOsc.hpp"
#include "OscTools.hpp"

///2.5D Events



class InputGestureTuio1125D : public Singleton<InputGestureTuio1125D>{
    struct addTuioCursor25DArgs: public EventArgs {int id; float xpos;float ypos;float zpos; float xspeed;float yspeed;float zspeed;float maccel;};
    struct updateTuioCursor25DArgs: public EventArgs {int id; float xpos;float ypos;float zpos; float xspeed;float yspeed;float zspeed;float maccel;};
    struct removeTuioCursor25DArgs: public EventArgs {int id;};
    struct addTuioObject25DArgs: public EventArgs {int id; int f_id ;float xpos;float ypos; float zpos; float angle; float xspeed;float yspeed; float zspeed; float rspeed;float maccel; float raccel;};
    struct updateTuioObject25DArgs: public EventArgs {int id; int f_id ;float xpos;float ypos; float zpos; float angle; float xspeed;float yspeed; float zspeed; float rspeed;float maccel; float raccel;};
    struct removeTuioObject25DArgs: public EventArgs {int id;};
    struct addTuioBlob25DArgs: public EventArgs {int id;float xpos;float ypos; float zpos; float angle; float width; float height; float area; float xspeed;float yspeed; float zspeed; float rspeed;float maccel; float raccel;};
    struct updateTuioBlob25DArgs: public EventArgs {int id;float xpos;float ypos; float zpos; float angle; float width; float height; float area; float xspeed;float yspeed; float zspeed; float rspeed;float maccel; float raccel;};
    struct removeTuioBlob25DArgs: public EventArgs {int id;};
    
    ofEvent<addTuioCursor25DArgs>       addTuioCursor25D;
    ofEvent<updateTuioCursor25DArgs>    updateTuioCursor25D;
    ofEvent<removeTuioCursor25DArgs>    removeTuioCursor25D;
    ofEvent<addTuioObject25DArgs>       addTuioObject25D;
    ofEvent<updateTuioObject25DArgs>    updateTuioObject25D;
    ofEvent<removeTuioObject25DArgs>    removeTuioObject25D;
    ofEvent<addTuioBlob25DArgs>         addTuioBlob25D;
    ofEvent<updateTuioBlob25DArgs>      updateTuioBlob25D;
    ofEvent<removeTuioBlob25DArgs>      removeTuioBlob25D;

    std::set<int> c_s_ids;
    std::set<int> o_s_ids;
    std::set<int> b_s_ids;

    public:
        InputGestureTuio1125D()
        {
            ofAddListener(InputGestureOSC::Instance().EventNewOScMessage,this,&InputGestureTuio1125D::ReceiveCall);
        }
        void ReceiveCall(InputGestureOSC::EventNewOScMessageArgs & args);
        void tuio25Dcur(OscOptionalUnpacker & argList);
        void tuio25Dobj(OscOptionalUnpacker & argList);
        void tuio25Dblb(OscOptionalUnpacker & argList);
};

/*
template <class Base>
class CanTuio1125D : public Base
{
    public:
    //Interface redefined by ofApp
    ///2.5D functions

    virtual void addTuioCursor25D(int id, float xpos,float ypos,float zpos, float xspeed,float yspeed,float zspeed,float maccel){}
    virtual void updateTuioCursor25D(int id, float xpos,float ypos,float zpos, float xspeed,float yspeed,float zspeed,float maccel){}
    virtual void removeTuioCursor25D(int id){}

    virtual void addTuioObject25D(int id, int f_id ,float xpos,float ypos, float zpos, float angle, float xspeed,float yspeed, float zspeed, float rspeed,float maccel, float raccel){}
    virtual void updateTuioObject25D(int id, int f_id ,float xpos,float ypos, float zpos, float angle, float xspeed,float yspeed, float zspeed, float rspeed,float maccel, float raccel){}
    virtual void removeTuioObject25D(int id){}

    virtual void addTuioBlob25D(int id,float xpos,float ypos, float zpos, float angle, float width, float height, float area, float xspeed,float yspeed, float zspeed, float rspeed,float maccel, float raccel){}
    virtual void updateTuioBlob25D(int id,float xpos,float ypos, float zpos, float angle, float width, float height, float area, float xspeed,float yspeed, float zspeed, float rspeed,float maccel, float raccel){}
    virtual void removeTuioBlob25D(int id){}

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


*/

#endif // INPUTGESTURETUIO1_12_5D_H_INCLUDED
