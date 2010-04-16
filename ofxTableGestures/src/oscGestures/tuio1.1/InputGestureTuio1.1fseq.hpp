/*

    OF-TangibleFramework . Framework for Taller de Sistemes Interactius I
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
