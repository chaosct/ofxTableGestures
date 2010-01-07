/*

    TSIframework . Framework for Taller de Sistemes Interactius I
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

#ifndef INPUTGESTUREDIRECTFINGERS_H_INCLUDED
#define INPUTGESTUREDIRECTFINGERS_H_INCLUDED

#include "InputGesture.h"
#include "TEvent.h"
#include "tuioApp.h"
#include <map>

using namespace osc;

namespace tuio
{


class DirectFinger
{
    public:
    int32 s_id;
    float xpos, ypos, xspeed, yspeed, maccel;
};

class TeventDirectFingersRemoveFinger : public TEvent
{
    public:
    TeventDirectFingersRemoveFinger():TEvent(event_dfinger_remove){}
    int32 s_id;
};

class TeventDirectFingersNewFinger : public TEvent
{
    public:
    TeventDirectFingersNewFinger():TEvent(event_dfinger_new){}
    int32 s_id;
    DirectFinger * df;
};



class InputGestureDirectFingers : public InputGesture {
    std::map<int32,DirectFinger *> fingers;
    int32 currentFrame, lastFrame;
    public:
        InputGestureDirectFingers():currentFrame(0),lastFrame(0){}
        virtual void ReceiveCall(const char * addr, osc::ReceivedMessageArgumentStream & argList);
};




template <class Base>
class CanDirectFingers : public  Base
{
    public:
    //Interface redefined by ofApp
    virtual void newCursor(int32 id, DirectFinger *){}
    virtual void removeCursor(int32 id){}

    //processing events callbacks
    TCallBack(CanDirectFingers,event_dfinger_remove);
    TEventHandler(event_dfinger_remove)
    {
        TeventDirectFingersRemoveFinger * e = static_cast<TeventDirectFingersRemoveFinger *>(evt);
        removeCursor(e->s_id);
    }
    TCallBack(CanDirectFingers,event_dfinger_new);
    TEventHandler(event_dfinger_new)
    {
        TeventDirectFingersNewFinger * e = static_cast<TeventDirectFingersNewFinger *>(evt);
        newCursor(e->s_id,e->df);
    }

    //registering
    CanDirectFingers()
    {
        TRegistraCallback(event_dfinger_remove);
        TRegistraCallback(event_dfinger_new);
        registerMeToInputGestureManager(Singleton<InputGestureDirectFingers>::get());
    }

    //allways needed
    eventprocessorsType & getEP()
    {
        return Base::getEP();
    }
};


}
#endif // INPUTGESTUREDIRECTFINGERS_H_INCLUDED
