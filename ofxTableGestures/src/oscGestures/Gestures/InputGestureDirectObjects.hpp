/*

    OF-TangibleFramework . Framework for Taller de Sistemes Interactius I
    Universitat Pompeu Fabra

    Copyright (c) 2009 Carles F. Julià <carles.fernandez@upf.edu>

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
#include "TEvent.hpp"
#include "DirectPoint.hpp"
#include <map>

using namespace osc;

namespace tuio
{


class DirectObject:public DirectPoint
{
    public:
        DirectObject(int32 _s_id, int32 _f_id, float _xpos, float _ypos,float _angle,float _xspeed,float _yspeed,float _rspeed,float _maccel,float _raccel):
            DirectPoint(_xpos,_ypos), s_id(_s_id), f_id(_f_id), angle(_angle), xspeed(_xspeed), yspeed(_yspeed), rspeed(_rspeed), maccel(_maccel), raccel(_raccel)
        {}
        DirectObject():DirectPoint(), s_id(-1), f_id(0), angle(0), xspeed(0), yspeed(0), rspeed(0), maccel(0), raccel(0){}
        DirectObject(const DirectObject& cpyobject): DirectPoint(cpyobject.xpos,cpyobject.ypos),s_id(cpyobject.s_id), f_id(cpyobject.f_id),
                                                    angle(cpyobject.angle), xspeed(cpyobject.xspeed), yspeed(cpyobject.yspeed),
                                                    rspeed(cpyobject.rspeed), maccel(cpyobject.maccel), raccel(cpyobject.raccel){
                                                    }
        int32 s_id, f_id;
        float angle, xspeed, yspeed, rspeed, maccel, raccel;
};

// Events definitions
SimpleDeclareEvent(CanDirectObjects,newObject,DirectObject *);
SimpleDeclareEvent(CanDirectObjects,removeObject,DirectObject *);
SimpleDeclareEvent(CanDirectObjects,updateObject,DirectObject *);

class InputGestureDirectObjects : public CanBasicObjects < CompositeGesture > {
    std::map<int32,DirectObject *> objects;
    public:
        InputGestureDirectObjects(){}
        void addTuioObject(int32 id, int32 f_id ,float xpos,float ypos, float angle, float xspeed,float yspeed,float rspeed,float maccel, float raccel);
        void updateTuioObject(int32 id, int32 f_id ,float xpos,float ypos, float angle, float xspeed,float yspeed,float rspeed,float maccel, float raccel);
        void removeTuioObject(int32 id);
};

template <class Base>
class CanDirectObjects : public  Base
{
    public:
    //Interface redefined by ofApp
    virtual void newObject(DirectObject * object){}
    virtual void removeObject(DirectObject * object){}
    virtual void updateObject(DirectObject * object);

    //registering
    CanDirectObjects()
    {
        SimpleRegisterEvent(CanDirectObjects,newObject);
        SimpleRegisterEvent(CanDirectObjects,removeObject);
        SimpleRegisterEvent(CanDirectObjects,updateObject);
        Base::template registerIG<InputGestureDirectObjects>();
    }

};


}
#endif // INPUTGESTUREDIRECTOBJECTS_H_INCLUDED
