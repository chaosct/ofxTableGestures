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

#ifndef INPUTGESTUREDIRECTOBJECTS_H_INCLUDED
#define INPUTGESTUREDIRECTOBJECTS_H_INCLUDED

#include "InputGestureBasicObjects.hpp"
#include "DirectPoint.hpp"
#include <map>




class DirectObject:public DirectPoint
{
public:
    DirectObject(int _s_id, int _f_id, float _xpos, float _ypos,float _angle,float _xspeed,float _yspeed,float _rspeed,float _maccel,float _raccel):
        DirectPoint(_xpos,_ypos), s_id(_s_id), f_id(_f_id), angle(_angle), xspeed(_xspeed), yspeed(_yspeed), rspeed(_rspeed), maccel(_maccel), raccel(_raccel)
    {}
    DirectObject():DirectPoint(), s_id(-1), f_id(0), angle(0), xspeed(0), yspeed(0), rspeed(0), maccel(0), raccel(0) {}
    DirectObject(const DirectObject& cpyobject): DirectPoint(cpyobject.xpos,cpyobject.ypos),s_id(cpyobject.s_id), f_id(cpyobject.f_id),
        angle(cpyobject.angle), xspeed(cpyobject.xspeed), yspeed(cpyobject.yspeed),
        rspeed(cpyobject.rspeed), maccel(cpyobject.maccel), raccel(cpyobject.raccel)
    {
    }
    int s_id, f_id;
    float angle, xspeed, yspeed, rspeed, maccel, raccel;
};



class InputGestureDirectObjects : public CanBasicObjects < CompositeGesture >, public Singleton<InputGestureDirectObjects>
{
    std::map<int,DirectObject *> objects;

    struct DirectObjectArgsBase: public EventArgs
    {
        DirectObject * object;
    };
public:

    typedef DirectObjectArgsBase newObjectArgs;
    typedef DirectObjectArgsBase removeObjectArgs;
    typedef DirectObjectArgsBase updateObjectArgs;
    typedef DirectObjectArgsBase enterObjectArgs;
    typedef DirectObjectArgsBase exitObjectArgs;
//    struct newObjectArgs: public EventArgs
//    {
//        DirectObject * object;
//    };
//    struct removeObjectArgs: public EventArgs
//    {
//        DirectObject * object;
//    };
//    struct updateObjectArgs: public EventArgs
//    {
//        DirectObject * object;
//    };
//    struct enterObjectArgs: public EventArgs
//    {
//        DirectObject * object;
//    };
//    struct exitObjectArgs: public EventArgs
//    {
//        DirectObject * object;
//    };

    ofEvent<newObjectArgs> newObject;
    ofEvent<removeObjectArgs> removeObject;
    ofEvent<updateObjectArgs> updateObject;
    ofEvent<enterObjectArgs> enterObject;
    ofEvent<exitObjectArgs> exitObject;

    InputGestureDirectObjects() {}
    void addTuioObject(int id, int f_id ,float xpos,float ypos, float angle, float xspeed,float yspeed,float rspeed,float maccel, float raccel);
    void enterTuioObject(int id, int f_id ,float xpos,float ypos, float angle, float xspeed,float yspeed,float rspeed,float maccel, float raccel);
    void updateTuioObject(int id, int f_id ,float xpos,float ypos, float angle, float xspeed,float yspeed,float rspeed,float maccel, float raccel);
    void removeTuioObject(int id);
    void exitTuioObject(int id);
};

template <class Base>
class CanDirectObjects : public  Base
{
public:
    void EnewObject(InputGestureDirectObjects::newObjectArgs & eventargs)
    {
        newObject(eventargs.object);
    }
    virtual void newObject(DirectObject * object) {}
    void EremoveObject(InputGestureDirectObjects::removeObjectArgs & eventargs)
    {
        removeObject(eventargs.object);
    }
    virtual void removeObject(DirectObject * object) {}
    void EupdateObject(InputGestureDirectObjects::updateObjectArgs & eventargs)
    {
        updateObject(eventargs.object);
    }
    virtual void updateObject(DirectObject * object) {}
    void EenterObject(InputGestureDirectObjects::enterObjectArgs & eventargs)
    {
        enterObject(eventargs.object);
    }
    virtual void enterObject(DirectObject * object)
    {
        newObject(object);
    }
    void EexitObject(InputGestureDirectObjects::exitObjectArgs & eventargs)
    {
        exitObject(eventargs.object);
    }
    virtual void exitObject(DirectObject * object)
    {
        removeObject(object);
    }

    //registering
    CanDirectObjects()
    {
        ofAddListener(InputGestureDirectObjects::Instance().newObject,this,&CanDirectObjects::EnewObject);
        ofAddListener(InputGestureDirectObjects::Instance().removeObject,this,&CanDirectObjects::EremoveObject);
        ofAddListener(InputGestureDirectObjects::Instance().updateObject,this,&CanDirectObjects::EupdateObject);
        ofAddListener(InputGestureDirectObjects::Instance().enterObject,this,&CanDirectObjects::EenterObject);
        ofAddListener(InputGestureDirectObjects::Instance().exitObject,this,&CanDirectObjects::EexitObject);
    }

    virtual ~CanDirectObjects()
    {
        ofRemoveListener(InputGestureDirectObjects::Instance().newObject,this,&CanDirectObjects::EnewObject);
        ofRemoveListener(InputGestureDirectObjects::Instance().removeObject,this,&CanDirectObjects::EremoveObject);
        ofRemoveListener(InputGestureDirectObjects::Instance().updateObject,this,&CanDirectObjects::EupdateObject);
        ofRemoveListener(InputGestureDirectObjects::Instance().enterObject,this,&CanDirectObjects::EenterObject);
        ofRemoveListener(InputGestureDirectObjects::Instance().exitObject,this,&CanDirectObjects::EexitObject);
    }

};



#endif // INPUTGESTUREDIRECTOBJECTS_H_INCLUDED
