#ifndef TUIO_INPUTGESTUREBASICFINGERS_H
#define TUIO_INPUTGESTUREBASICFINGERS_H

#include "osc/OscReceivedElements.h"
#include "InputGesture.h"
#include "TEvent.h"
#include <set>
#include "tuioApp.h"
using namespace osc;

namespace tuio {

class TeventBasicFingersRemoveFinger : public TEvent
{
    public:
    TeventBasicFingersRemoveFinger():TEvent(event_finger_remove){}
    int32 s_id;
};

class TeventBasicFingersNewFinger : public TEvent
{
    public:
    TeventBasicFingersNewFinger():TEvent(event_finger_new){}
    int32 s_id;
    float xpos, ypos, xspeed, yspeed, maccel;
};

class TeventBasicFingersMoveFinger : public TEvent
{
    public:
    TeventBasicFingersMoveFinger():TEvent(event_finger_move){}
    int32 s_id;
    float xpos, ypos, xspeed, yspeed, maccel;
};

class InputGestureBasicFingers : public InputGesture {
    std::set<int32> s_ids;
    int32 currentFrame, lastFrame;
    public:
        InputGestureBasicFingers():currentFrame(0),lastFrame(0){s_ids.empty();}
        virtual void ReceiveCall(const char * addr, osc::ReceivedMessageArgumentStream & argList);
};

template <class Base>
class CanBasicFingers : public Base
{
    public:
    //Interface redefined by ofApp
    virtual void addTuioCursor(int32 id, float xpos,float ypos,float xspeed,float yspeed,float maccel){}
    virtual void updateTuioCursor(int32 id, float xpos,float ypos,float xspeed,float yspeed,float maccel){}
    virtual void removeTuioCursor(int32 id){}

    //processing events callbacks
    TCallBack(CanBasicFingers,event_finger_remove);
    TEventHandler(event_finger_remove)
    {
        TeventBasicFingersRemoveFinger * e = static_cast<TeventBasicFingersRemoveFinger *>(evt);
        removeTuioCursor(e->s_id);
    }
    TCallBack(CanBasicFingers,event_finger_new);
    TEventHandler(event_finger_new)
    {
        TeventBasicFingersNewFinger * e = static_cast<TeventBasicFingersNewFinger *>(evt);
        addTuioCursor(e->s_id,e->xpos, e->ypos, e->xspeed, e->yspeed, e->maccel);
    }
    TCallBack(CanBasicFingers,event_finger_move);
    TEventHandler(event_finger_move)
    {
        TeventBasicFingersMoveFinger * e = static_cast<TeventBasicFingersMoveFinger *>(evt);
        updateTuioCursor(e->s_id,e->xpos, e->ypos, e->xspeed, e->yspeed, e->maccel);
    }

    //registering
    CanBasicFingers()
    {
        TRegistraCallback(event_finger_remove);
        TRegistraCallback(event_finger_new);
        TRegistraCallback(event_finger_move);
    }

    //allways needed
    eventprocessorsType & getEP()
    {
        return Base::getEP();
    }
};

} // namespace tuio
#endif
