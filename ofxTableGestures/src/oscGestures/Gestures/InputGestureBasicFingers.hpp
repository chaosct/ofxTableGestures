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

#ifndef TUIO_INPUTGESTUREBASICFINGERS_H
#define TUIO_INPUTGESTUREBASICFINGERS_H

#include "OscReceivedElements.h"
#include "InputGesture.hpp"
#include "TEvent.hpp"
#include <set>
#include "tuioApp.hpp"
#include "InputGestureTuio1.1.hpp"

using osc::int32;

namespace tuio {

SimpleDeclareEvent(CanBasicFingers,removeTuioCursor,int32);
SimpleDeclareEvent(CanBasicFingers,addTuioCursor,int32,float,float,float,float,float);
SimpleDeclareEvent(CanBasicFingers,updateTuioCursor,int32,float,float,float,float,float);


class InputGestureBasicFingers : public  CanTuio112D<CompositeGesture>
{
    public:
        InputGestureBasicFingers(){}
        void addTuioCursor2D(int32 id, float xpos,float ypos,float xspeed,float yspeed,float maccel)
        {
            SimpleCallEvent(CanBasicFingers,addTuioCursor,(id,xpos,ypos,xspeed,yspeed,maccel));
        }
        void updateTuioCursor2D(int32 id, float xpos,float ypos,float xspeed,float yspeed,float maccel)
        {
            SimpleCallEvent(CanBasicFingers,updateTuioCursor,(id,xpos,ypos,xspeed,yspeed,maccel));
        }
        void removeTuioCursor2D(int32 id)
        {
            SimpleCallEvent(CanBasicFingers,removeTuioCursor,(id));
        }

};

template <class Base>
class CanBasicFingers : public Base
{
    public:
    //Interface redefined by ofApp
    virtual void addTuioCursor(int32 id, float xpos,float ypos,float xspeed,float yspeed,float maccel){}
    virtual void updateTuioCursor(int32 id, float xpos,float ypos,float xspeed,float yspeed,float maccel){}
    virtual void removeTuioCursor(int32 id){}

    //registering
    void Register(Area * a)
    {
        Base::Register(a);
        SimpleRegisterEvent(CanBasicFingers,addTuioCursor);
        SimpleRegisterEvent(CanBasicFingers,updateTuioCursor);
        SimpleRegisterEvent(CanBasicFingers,removeTuioCursor);
        Base::template registerIG<InputGestureBasicFingers>();
    }
};

} // namespace tuio
#endif
