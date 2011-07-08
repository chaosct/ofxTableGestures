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

#ifndef TUIO_INPUTGESTUREBASICOBJECTS_H
#define TUIO_INPUTGESTUREBASICOBJECTS_H

#include <set>
#include "InputGestureTuio1.1.hpp"

struct commonObjectArgs : public commonIdArgs
{
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

class InputGestureBasicObjects : public  EventClient, public Singleton<InputGestureBasicObjects>
{


public:

    typedef commonObjectArgs addTuioObjectArgs;
    typedef commonObjectArgs updateTuioObjectArgs;
    typedef commonIdArgs removeTuioObjectArgs;
    typedef commonIdArgs exitTuioObjectArgs;
    typedef commonObjectArgs enterTuioObjectArgs;

    ofEvent<removeTuioObjectArgs> removeTuioObject;
    ofEvent<exitTuioObjectArgs> exitTuioObject;
    ofEvent<addTuioObjectArgs> addTuioObject;
    ofEvent<enterTuioObjectArgs> enterTuioObject;
    ofEvent<updateTuioObjectArgs> updateTuioObject;

///Internal stuff

private:

    std::map<int,Graphic * > graphic_assignations;
    std::set<int> ids;

public:

    InputGestureBasicObjects();
    void addTuioObject2D(int id, int f_id ,float xpos,float ypos, float angle, float xspeed,float yspeed,float rspeed,float maccel, float raccel);
    void updateTuioObject2D(int id, int f_id ,float xpos,float ypos, float angle, float xspeed,float yspeed,float rspeed,float maccel, float raccel);
    void removeTuioObject2D(int id);
    void addTuioObject2D(InputGestureTuio112D::addTuioObject2DArgs & eventargs)
    {
        addTuioObject2D(eventargs.id,eventargs.f_id,eventargs.xpos,eventargs.ypos,eventargs.angle,eventargs.xspeed,eventargs.yspeed,eventargs.rspeed,eventargs.maccel,eventargs.raccel);
    }
    void updateTuioObject2D(InputGestureTuio112D::updateTuioObject2DArgs & eventargs)
    {
        updateTuioObject2D(eventargs.id,eventargs.f_id,eventargs.xpos,eventargs.ypos,eventargs.angle,eventargs.xspeed,eventargs.yspeed,eventargs.rspeed,eventargs.maccel,eventargs.raccel);
    }
    void removeTuioObject2D(InputGestureTuio112D::removeTuioObject2DArgs & eventargs)
    {
        removeTuioObject2D(eventargs.id);
    }

};


template <class Base>
class CanBasicObjects : public Base
{
public:
    void EaddTuioObject(InputGestureBasicObjects::addTuioObjectArgs & eventargs)
    {
        addTuioObject(eventargs.id,eventargs.f_id,eventargs.xpos,eventargs.ypos,eventargs.angle,eventargs.xspeed,eventargs.yspeed,eventargs.rspeed,eventargs.maccel,eventargs.raccel);
    }
    virtual void addTuioObject(int id, int f_id ,float xpos,float ypos, float angle, float xspeed,float yspeed,float rspeed,float maccel, float raccel) {}
    void EupdateTuioObject(InputGestureBasicObjects::updateTuioObjectArgs & eventargs)
    {
        updateTuioObject(eventargs.id,eventargs.f_id,eventargs.xpos,eventargs.ypos,eventargs.angle,eventargs.xspeed,eventargs.yspeed,eventargs.rspeed,eventargs.maccel,eventargs.raccel);
    }
    virtual void updateTuioObject(int id, int f_id ,float xpos,float ypos, float angle, float xspeed,float yspeed,float rspeed,float maccel, float raccel) {}
    void EremoveTuioObject(InputGestureBasicObjects::removeTuioObjectArgs & eventargs)
    {
        removeTuioObject(eventargs.id);
    }
    virtual void removeTuioObject(int id) {}
    void EenterTuioObject(InputGestureBasicObjects::enterTuioObjectArgs & eventargs)
    {
        enterTuioObject(eventargs.id,eventargs.f_id,eventargs.xpos,eventargs.ypos,eventargs.angle,eventargs.xspeed,eventargs.yspeed,eventargs.rspeed,eventargs.maccel,eventargs.raccel);
    }
    virtual void enterTuioObject(int id, int f_id ,float xpos,float ypos, float angle, float xspeed,float yspeed,float rspeed,float maccel, float raccel)
    {
        addTuioObject(id, f_id , xpos, ypos, angle, xspeed, yspeed, rspeed, maccel, raccel);
    }
    void EexitTuioObject(InputGestureBasicObjects::exitTuioObjectArgs & eventargs)
    {
        exitTuioObject(eventargs.id);
    }
    virtual void exitTuioObject(int id)
    {
        removeTuioObject(id);
    }

    //registering
    CanBasicObjects()
    {
        ofAddListener(InputGestureBasicObjects::Instance().addTuioObject,this,&CanBasicObjects::EaddTuioObject);
        ofAddListener(InputGestureBasicObjects::Instance().updateTuioObject,this,&CanBasicObjects::EupdateTuioObject);
        ofAddListener(InputGestureBasicObjects::Instance().removeTuioObject,this,&CanBasicObjects::EremoveTuioObject);
        ofAddListener(InputGestureBasicObjects::Instance().enterTuioObject,this,&CanBasicObjects::EenterTuioObject);
        ofAddListener(InputGestureBasicObjects::Instance().exitTuioObject,this,&CanBasicObjects::EexitTuioObject);
    }
    virtual ~CanBasicObjects()
    {
        ofRemoveListener(InputGestureBasicObjects::Instance().addTuioObject,this,&CanBasicObjects::EaddTuioObject);
        ofRemoveListener(InputGestureBasicObjects::Instance().updateTuioObject,this,&CanBasicObjects::EupdateTuioObject);
        ofRemoveListener(InputGestureBasicObjects::Instance().removeTuioObject,this,&CanBasicObjects::EremoveTuioObject);
        ofRemoveListener(InputGestureBasicObjects::Instance().enterTuioObject,this,&CanBasicObjects::EenterTuioObject);
        ofRemoveListener(InputGestureBasicObjects::Instance().exitTuioObject,this,&CanBasicObjects::EexitTuioObject);
    }

};

#endif
