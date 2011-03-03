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

#ifndef INPUTGESTURETUIO1_12D_H_INCLUDED
#define INPUTGESTURETUIO1_12D_H_INCLUDED


#include <set>

#include "GlobalConfig.hpp"
#include "InputGestureOsc.hpp"
#include "OscTools.hpp"

class InputGestureTuio112D  : public Singleton<InputGestureTuio112D>
{
    public:
    struct addTuioCursor2DArgs:     public EventArgs
    {
        int id;
        float xpos;
        float ypos;
        float xspeed;
        float yspeed;
        float maccel;
    };
    struct updateTuioCursor2DArgs:  public EventArgs
    {
        int id;
        float xpos;
        float ypos;
        float xspeed;
        float yspeed;
        float maccel;
    };
    struct removeTuioCursor2DArgs:  public EventArgs
    {
        int id;
    };
    struct addTuioObject2DArgs:     public EventArgs
    {
        int id;
        int f_id ;
        float xpos;
        float ypos;
        float angle;
        float xspeed;
        float yspeed;
        float rspeed;
        float maccel;
        float raccel;
    };
    struct updateTuioObject2DArgs:  public EventArgs
    {
        int id;
        int f_id ;
        float xpos;
        float ypos;
        float angle;
        float xspeed;
        float yspeed;
        float rspeed;
        float maccel;
        float raccel;
    };
    struct removeTuioObject2DArgs:  public EventArgs
    {
        int id;
    };
    struct addTuioBlob2DArgs:       public EventArgs
    {
        int id;
        float xpos;
        float ypos;
        float angle;
        float width;
        float height;
        float area;
        float xspeed;
        float yspeed;
        float rspeed;
        float maccel;
        float raccel;
    };
    struct updateTuioBlob2DArgs:    public EventArgs
    {
        int id;
        float xpos;
        float ypos;
        float angle;
        float width;
        float height;
        float area;
        float xspeed;
        float yspeed;
        float rspeed;
        float maccel;
        float raccel;
    };
    struct removeTuioBlob2DArgs:    public EventArgs
    {
        int id;
    };

    ofEvent<addTuioCursor2DArgs>    addTuioCursor2D;
    ofEvent<updateTuioCursor2DArgs> updateTuioCursor2D;
    ofEvent<removeTuioCursor2DArgs> removeTuioCursor2D;
    ofEvent<addTuioObject2DArgs>    addTuioObject2D;
    ofEvent<updateTuioObject2DArgs> updateTuioObject2D;
    ofEvent<removeTuioObject2DArgs> removeTuioObject2D;
    ofEvent<addTuioBlob2DArgs>      addTuioBlob2D;
    ofEvent<updateTuioBlob2DArgs>   updateTuioBlob2D;
    ofEvent<removeTuioBlob2DArgs>   removeTuioBlob2D;

    std::set<int> c_s_ids;
    std::set<int> o_s_ids;
    std::set<int> b_s_ids;

    int & squaredInterface;
    InputGestureTuio112D():
        squaredInterface(GlobalConfig::getRef("GLOBAL:SQUAREDINTERFACE",1))
    {
        ofAddListener(InputGestureOSC::Instance().EventNewOScMessage,this,&InputGestureTuio112D::ReceiveCall);
    }
    void ReceiveCall(InputGestureOSC::EventNewOScMessageArgs & args);
    void tuio2Dcur(OscOptionalUnpacker & argList);
    void tuio2Dobj(OscOptionalUnpacker & argList);
    void tuio2Dblb(OscOptionalUnpacker & argList);

};


template <class Base>
class CanTuio112D : public Base
{
public:
    //Interface redefined by ofApp
    ///2D functions
    void EaddTuioCursor2D(InputGestureTuio112D::addTuioCursor2DArgs & eventargs)
    {
        addTuioCursor2D(eventargs.id,eventargs.xpos,eventargs.ypos,eventargs.xspeed,eventargs.yspeed,eventargs.maccel);
    }
    virtual void addTuioCursor2D(int id, float xpos,float ypos,float xspeed,float yspeed,float maccel) {}
    void EupdateTuioCursor2D(InputGestureTuio112D::updateTuioCursor2DArgs & eventargs)
    {
        updateTuioCursor2D(eventargs.id,eventargs.xpos,eventargs.ypos,eventargs.xspeed,eventargs.yspeed,eventargs.maccel);
    }
    virtual void updateTuioCursor2D(int id, float xpos,float ypos,float xspeed,float yspeed,float maccel) {}
    void EremoveTuioCursor2D(InputGestureTuio112D::removeTuioCursor2DArgs & eventargs)
    {
        removeTuioCursor2D(eventargs.id);
    }
    virtual void removeTuioCursor2D(int id) {}
    void EaddTuioObject2D(InputGestureTuio112D::addTuioObject2DArgs & eventargs)
    {
        addTuioObject2D(eventargs.id,eventargs.f_id,eventargs.xpos,eventargs.ypos,eventargs.angle,eventargs.xspeed,eventargs.yspeed,eventargs.rspeed,eventargs.maccel,eventargs.raccel);
    }
    virtual void addTuioObject2D(int id, int f_id ,float xpos,float ypos, float angle, float xspeed,float yspeed,float rspeed,float maccel, float raccel) {}
    void EupdateTuioObject2D(InputGestureTuio112D::updateTuioObject2DArgs & eventargs)
    {
        updateTuioObject2D(eventargs.id,eventargs.f_id,eventargs.xpos,eventargs.ypos,eventargs.angle,eventargs.xspeed,eventargs.yspeed,eventargs.rspeed,eventargs.maccel,eventargs.raccel);
    }
    virtual void updateTuioObject2D(int id, int f_id ,float xpos,float ypos, float angle, float xspeed,float yspeed,float rspeed,float maccel, float raccel) {}
    void EremoveTuioObject2D(InputGestureTuio112D::removeTuioObject2DArgs & eventargs)
    {
        removeTuioObject2D(eventargs.id);
    }
    virtual void removeTuioObject2D(int id) {}
    void EaddTuioBlob2D(InputGestureTuio112D::addTuioBlob2DArgs & eventargs)
    {
        addTuioBlob2D(eventargs.id,eventargs.xpos,eventargs.ypos,eventargs.angle,eventargs.width,eventargs.height,eventargs.area,eventargs.xspeed,eventargs.yspeed,eventargs.rspeed,eventargs.maccel,eventargs.raccel);
    }
    virtual void addTuioBlob2D(int id,float xpos,float ypos, float angle, float width, float height, float area, float xspeed,float yspeed,float rspeed,float maccel, float raccel) {}
    void EupdateTuioBlob2D(InputGestureTuio112D::updateTuioBlob2DArgs & eventargs)
    {
        updateTuioBlob2D(eventargs.id,eventargs.xpos,eventargs.ypos,eventargs.angle,eventargs.width,eventargs.height,eventargs.area,eventargs.xspeed,eventargs.yspeed,eventargs.rspeed,eventargs.maccel,eventargs.raccel);
    }
    virtual void updateTuioBlob2D(int id,float xpos,float ypos, float angle, float width, float height, float area, float xspeed,float yspeed,float rspeed,float maccel, float raccel) {}
    void EremoveTuioBlob2D(InputGestureTuio112D::removeTuioBlob2DArgs & eventargs)
    {
        removeTuioBlob2D(eventargs.id);
    }
    virtual void removeTuioBlob2D(int id) {}

    //registering
    CanTuio112D()
    {

        ///2D Events

        ofAddListener(InputGestureTuio112D::Instance().removeTuioCursor2D,this,&CanTuio112D::EremoveTuioCursor2D);
        ofAddListener(InputGestureTuio112D::Instance().addTuioCursor2D,this,&CanTuio112D::EaddTuioCursor2D);
        ofAddListener(InputGestureTuio112D::Instance().updateTuioCursor2D,this,&CanTuio112D::EupdateTuioCursor2D);

        ofAddListener(InputGestureTuio112D::Instance().addTuioObject2D,this,&CanTuio112D::EaddTuioObject2D);
        ofAddListener(InputGestureTuio112D::Instance().updateTuioObject2D,this,&CanTuio112D::EupdateTuioObject2D);
        ofAddListener(InputGestureTuio112D::Instance().removeTuioObject2D,this,&CanTuio112D::EremoveTuioObject2D);

        ofAddListener(InputGestureTuio112D::Instance().addTuioBlob2D,this,&CanTuio112D::EaddTuioBlob2D);
        ofAddListener(InputGestureTuio112D::Instance().updateTuioBlob2D,this,&CanTuio112D::EupdateTuioBlob2D);
        ofAddListener(InputGestureTuio112D::Instance().removeTuioBlob2D,this,&CanTuio112D::EremoveTuioBlob2D);

    }
};




#endif // INPUTGESTURETUIO1_12D_H_INCLUDED
