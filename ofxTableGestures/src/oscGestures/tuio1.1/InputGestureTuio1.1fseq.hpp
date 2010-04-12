#ifndef INPUTGESTURETUIO1_1FSEQ_H_INCLUDED
#define INPUTGESTURETUIO1_1FSEQ_H_INCLUDED

#include "OscReceivedElements.h"
#include "InputGesture.hpp"
#include "TEvent.hpp"
#include "tuioApp.hpp"
#include <cstring>

using osc::int32;

namespace tuio
{

SimpleDeclareEvent(CanTuio11ValidBundle,isvalid,bool);

class InputGestureTuio11ValidBundle : public InputGesture
{
    int32 lastFrame;
    public:
    InputGestureTuio11ValidBundle():lastFrame(0){}
    void ReceiveCall(const char * addr, osc::ReceivedMessageArgumentStream & args)
    {
    if( strcmp( addr, "/tuio/2Dcur" ) == 0  || strcmp( addr, "/tuio/2Dobj" ) == 0 ||
        strcmp( addr, "/tuio/3Dcur" ) == 0  || strcmp( addr, "/tuio/3Dobj" ) == 0 ||
        strcmp( addr, "/tuio/25Dcur" ) == 0 || strcmp( addr, "/tuio/25Dobj" ) == 0 )
        {
            const char* cmd;
            args >> cmd;
            if( strcmp(cmd,"fseq") == 0)
            {
                int32 frame;
                args >> frame  >> osc::EndMessage;
                if(frame == -1 )
                {
                    SimpleCallEvent(CanTuio11ValidBundle,isvalid,(true));
                    return;
                }
                if (frame < lastFrame)
                {
                    SimpleCallEvent(CanTuio11ValidBundle,isvalid,(false));
                }
                else
                {
                    SimpleCallEvent(CanTuio11ValidBundle,isvalid,(true));
                }
                lastFrame = frame;
            }
        }
    }

};


template <class Base>
class CanTuio11ValidBundle : public Base
{
    public:
    //interface
    virtual void isvalid(bool v){}

    CanTuio11ValidBundle()
    {
        SimpleRegisterEvent(CanTuio11ValidBundle,isvalid);
        Base::template registerIG<InputGestureTuio11ValidBundle>();
    }
};

}

#endif // INPUTGESTURETUIO1_1FSEQ_H_INCLUDED
