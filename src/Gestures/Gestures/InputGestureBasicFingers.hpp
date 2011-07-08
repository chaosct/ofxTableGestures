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

#ifndef TUIO_INPUTGESTUREBASICFINGERS_H
#define TUIO_INPUTGESTUREBASICFINGERS_H

#include <set>
#include "InputGestureTuio1.1.hpp"


struct commonCursorArgs : public commonIdArgs
{
    float xpos;
    float ypos;
    float xspeed;
    float yspeed;
    float maccel;
};

class InputGestureBasicFingers : public  EventClient, public Singleton<InputGestureBasicFingers>
{


public:

    typedef commonCursorArgs addTuioCursorArgs;
    typedef commonCursorArgs updateTuioCursorArgs;
    typedef commonIdArgs removeTuioCursorArgs;
    typedef commonIdArgs exitTuioCursorArgs;
    typedef commonCursorArgs enterTuioCursorArgs;

    ofEvent<removeTuioCursorArgs> removeTuioCursor;
    ofEvent<exitTuioCursorArgs> exitTuioCursor;
    ofEvent<addTuioCursorArgs> addTuioCursor;
    ofEvent<enterTuioCursorArgs> enterTuioCursor;
    ofEvent<updateTuioCursorArgs> updateTuioCursor;

///Internal stuff

private:

    std::map<int,Graphic * > graphic_assignations;
    std::set<int> ids;

public:

    InputGestureBasicFingers();
    void addTuioCursor2D(int id, float xpos,float ypos,float xspeed,float yspeed,float maccel);
    void updateTuioCursor2D(int id, float xpos,float ypos,float xspeed,float yspeed,float maccel);
    void removeTuioCursor2D(int id);
    void addTuioCursor2D(InputGestureTuio112D::addTuioCursor2DArgs & eventargs)
    {
        addTuioCursor2D(eventargs.id,eventargs.xpos,eventargs.ypos,eventargs.xspeed,eventargs.yspeed,eventargs.maccel);
    }
    void updateTuioCursor2D(InputGestureTuio112D::updateTuioCursor2DArgs & eventargs)
    {
        updateTuioCursor2D(eventargs.id,eventargs.xpos,eventargs.ypos,eventargs.xspeed,eventargs.yspeed,eventargs.maccel);
    }
    void removeTuioCursor2D(InputGestureTuio112D::removeTuioCursor2DArgs & eventargs)
    {
        removeTuioCursor2D(eventargs.id);
    }

};


template <class Base>
class CanBasicFingers : public Base
{

public:
    void EaddTuioCursor(InputGestureBasicFingers::addTuioCursorArgs & eventargs)
    {
        addTuioCursor(eventargs.id,eventargs.xpos,eventargs.ypos,eventargs.xspeed,eventargs.yspeed,eventargs.maccel);
    }
    virtual void addTuioCursor(int id, float xpos,float ypos,float xspeed,float yspeed,float maccel) {}
    void EupdateTuioCursor(InputGestureBasicFingers::updateTuioCursorArgs & eventargs)
    {
        updateTuioCursor(eventargs.id,eventargs.xpos,eventargs.ypos,eventargs.xspeed,eventargs.yspeed,eventargs.maccel);
    }
    virtual void updateTuioCursor(int id, float xpos,float ypos,float xspeed,float yspeed,float maccel) {}
    void EremoveTuioCursor(InputGestureBasicFingers::removeTuioCursorArgs & eventargs)
    {
        removeTuioCursor(eventargs.id);
    }
    virtual void removeTuioCursor(int id) {}
    void EexitTuioCursor(InputGestureBasicFingers::exitTuioCursorArgs & eventargs)
    {
        exitTuioCursor(eventargs.id);
    }
    virtual void exitTuioCursor(int id)
    {
        removeTuioCursor(id);
    }
    void EenterTuioCursor(InputGestureBasicFingers::enterTuioCursorArgs & eventargs)
    {
        enterTuioCursor(eventargs.id,eventargs.xpos,eventargs.ypos,eventargs.xspeed,eventargs.yspeed,eventargs.maccel);
    }
    virtual void enterTuioCursor(int id, float xpos,float ypos,float xspeed,float yspeed,float maccel)
    {
        addTuioCursor(id,xpos,ypos,xspeed,yspeed,maccel);
    }
//    //Interface redefined by ofApp
//    virtual void addTuioCursor(int id, float xpos,float ypos,float xspeed,float yspeed,float maccel){}
//    virtual void updateTuioCursor(int id, float xpos,float ypos,float xspeed,float yspeed,float maccel){}
//    virtual void removeTuioCursor(int id){}
//    //Area-aware interface optionally redefined by ofApp
//    virtual void exitTuioCursor(int id)                                                                   {removeTuioCursor(id);}
//    virtual void enterTuioCursor(int id, float xpos,float ypos,float xspeed,float yspeed,float maccel)    {addTuioCursor(id,xpos,ypos,xspeed,yspeed,maccel);}

    //registering
    CanBasicFingers()
    {

        ofAddListener(InputGestureBasicFingers::Instance().addTuioCursor,this,&CanBasicFingers::EaddTuioCursor);
        ofAddListener(InputGestureBasicFingers::Instance().enterTuioCursor,this,&CanBasicFingers::EenterTuioCursor);
        ofAddListener(InputGestureBasicFingers::Instance().updateTuioCursor,this,&CanBasicFingers::EupdateTuioCursor);
        ofAddListener(InputGestureBasicFingers::Instance().removeTuioCursor,this,&CanBasicFingers::EremoveTuioCursor);
        ofAddListener(InputGestureBasicFingers::Instance().exitTuioCursor,this,&CanBasicFingers::EexitTuioCursor);

    }
    virtual ~CanBasicFingers()
    {

        ofRemoveListener(InputGestureBasicFingers::Instance().addTuioCursor,this,&CanBasicFingers::EaddTuioCursor);
        ofRemoveListener(InputGestureBasicFingers::Instance().enterTuioCursor,this,&CanBasicFingers::EenterTuioCursor);
        ofRemoveListener(InputGestureBasicFingers::Instance().updateTuioCursor,this,&CanBasicFingers::EupdateTuioCursor);
        ofRemoveListener(InputGestureBasicFingers::Instance().removeTuioCursor,this,&CanBasicFingers::EremoveTuioCursor);
        ofRemoveListener(InputGestureBasicFingers::Instance().exitTuioCursor,this,&CanBasicFingers::EexitTuioCursor);

    }

};


#endif
