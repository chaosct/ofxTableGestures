#ifndef INPUTGESTURETUIO1_1FSEQ_H_INCLUDED
#define INPUTGESTURETUIO1_1FSEQ_H_INCLUDED

#include "OscReceivedElements.h"
#include "InputGesture.h"
#include "TEvent.h"
#include "tuioApp.h"
#include <cstring>

using osc::int32;

namespace tuio
{

class TEventTuio11ValidBundle : public TTEvent<TEventTuio11ValidBundle>
{
public:
    bool valid;
    TEventTuio11ValidBundle(bool Valid = true):valid(Valid) {}
};

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
                    events.push_back(new TEventTuio11ValidBundle(true));
                    return;
                }
                if (frame < lastFrame)
                {
                    events.push_back(new TEventTuio11ValidBundle(false));
                }
                else
                {
                    events.push_back(new TEventTuio11ValidBundle(true));
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

    TEventHandler(TEventTuio11ValidBundle)
    {
        TEventTuio11ValidBundle * e = static_cast<TEventTuio11ValidBundle *>(evt);
        isvalid(e->valid);
    }

    CanTuio11ValidBundle()
    {
        TRegistraCallback(CanTuio11ValidBundle,TEventTuio11ValidBundle);
        Base::registerInputGesture(Singleton<InputGestureTuio11ValidBundle>::get());
    }
};

}

#endif // INPUTGESTURETUIO1_1FSEQ_H_INCLUDED
