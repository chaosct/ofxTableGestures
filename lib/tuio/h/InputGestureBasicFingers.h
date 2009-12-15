#ifndef TUIO_INPUTGESTUREBASICFINGERS_H
#define TUIO_INPUTGESTUREBASICFINGERS_H

#include "osc/OscReceivedElements.h"
#include "InputGesture.h"
#include <set>

using namespace osc;

namespace tuio {

class InputGestureBasicFingers : public InputGesture {
    std::set<int32> s_ids;
    int32 currentFrame, lastFrame;
    public:
        InputGestureBasicFingers():currentFrame(0),lastFrame(0){s_ids.empty();}
        virtual void ReceiveCall(const char * addr, osc::ReceivedMessageArgumentStream & argList);
};

class TeventBasicFingersRemoveFinger : public TEvent
{
    public:
    TeventBasicFingersRemoveFinger()
    {
        name = "finger.remove";
    }
    int32 s_id;
};

class TeventBasicFingersNewFinger : public TEvent
{
    public:
    TeventBasicFingersNewFinger()
    {
        name = "finger.new";
    }
    int32 s_id;
    float xpos, ypos, xspeed, yspeed, maccel;
};

class TeventBasicFingersMoveFinger : public TEvent
{
    public:
    TeventBasicFingersMoveFinger()
    {
        name = "finger.move";
    }
    int32 s_id;
    float xpos, ypos, xspeed, yspeed, maccel;
};

} // namespace tuio
#endif
