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

#ifndef TUIO_INPUTGESTUREBASICOBJECTS_H
#define TUIO_INPUTGESTUREBASICOBJECTS_H

#include "OscReceivedElements.h"
#include "InputGesture.hpp"
#include <set>
#include "TEvent.hpp"
#include "tuioApp.hpp"
#include "InputGestureTuio1.1.hpp"

using namespace osc;

namespace tuio
{

SimpleDeclareEvent(CanBasicObjects,removeTuioObject,    int32);
SimpleDeclareEvent(CanBasicObjects,addTuioObject,       int32 , int32  ,float ,float , float , float ,float ,float ,float , float );
SimpleDeclareEvent(CanBasicObjects,updateTuioObject,    int32 , int32  ,float ,float , float , float ,float ,float ,float , float );


class InputGestureBasicObjects : public CanTuio112D < CompositeGesture >
{
public:
    InputGestureBasicObjects() {}
    void addTuioObject2D(int32 id, int32 f_id ,float xpos,float ypos, float angle, float xspeed,float yspeed,float rspeed,float maccel, float raccel)
    {
        SimpleCallEvent(CanBasicObjects,addTuioObject,(id, f_id , xpos, ypos,  angle,  xspeed, yspeed, rspeed, maccel,  raccel));
    }
    void updateTuioObject2D(int32 id, int32 f_id ,float xpos,float ypos, float angle, float xspeed,float yspeed,float rspeed,float maccel, float raccel)
    {
        SimpleCallEvent(CanBasicObjects,updateTuioObject,(id, f_id , xpos, ypos,  angle,  xspeed, yspeed, rspeed, maccel,  raccel));
    }
    void removeTuioObject2D(int32 id)
    {
        SimpleCallEvent(CanBasicObjects,removeTuioObject,(id));
    }
};

template <class Base>
class CanBasicObjects : public Base
{
public:
    //Interface redefined by ofApp
    virtual void addTuioObject(int32 id, int32 f_id ,float xpos,float ypos, float angle, float xspeed,float yspeed,float rspeed,float maccel, float raccel) {}
    virtual void updateTuioObject(int32 id, int32 f_id ,float xpos,float ypos, float angle, float xspeed,float yspeed,float rspeed,float maccel, float raccel) {}
    virtual void removeTuioObject(int32 id) {}

    //registering
    void Register(Area * a)
    {
        Base::Register(a);
        SimpleRegisterEvent(CanBasicObjects,addTuioObject);
        SimpleRegisterEvent(CanBasicObjects,updateTuioObject);
        SimpleRegisterEvent(CanBasicObjects,removeTuioObject);

        Base::template registerIG<InputGestureBasicObjects>();
    }

};

} // namespace tuio
#endif
