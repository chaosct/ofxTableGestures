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

#include "InputGestureTuio1.13D.hpp"
#include <cstring>

using namespace osc;

namespace tuio
{

void InputGestureTuio113D::ReceiveCall(const char * addr, ReceivedMessageArgumentStream & args)
{
    if(!valid)
        return;
    if( strcmp( addr, "/tuio/3Dcur" ) == 0 )
        tuio3Dcur(args);
    if( strcmp( addr, "/tuio/3Dobj" ) == 0 )
        tuio3Dobj(args);
}

void InputGestureTuio113D::tuio3Dcur(ReceivedMessageArgumentStream & args)
{
    const char* cmd;
    args >> cmd;

    if(strcmp(cmd,"set")== 0)
    {
        int32 s_id;
        float xpos, ypos, zpos, xspeed, yspeed, zspeed, maccel;

        args >> s_id >> xpos >> ypos >> zpos >> xspeed >> yspeed >> zspeed >> maccel >> EndMessage;

        if(c_s_ids.find(s_id) == c_s_ids.end())
        {
            SimpleCallEvent(CanTuio113D,addTuioCursor3D,(s_id, xpos, ypos, zpos, xspeed, yspeed, zspeed, maccel));
            c_s_ids.insert(s_id);
        }
        else
        {
            SimpleCallEvent(CanTuio113D,updateTuioCursor3D,(s_id, xpos, ypos, zpos, xspeed, yspeed, zspeed, maccel));
        }

    }
    else if( strcmp( cmd, "alive" ) == 0 )
    {
        int32 s_id;
        std::set<int32> t(c_s_ids);
        while(!args.Eos())
        {
            args >> s_id;
            t.erase(s_id);
        }
        args >> EndMessage;
        for (std::set<int32>::iterator it = t.begin(); it != t.end(); ++it)
        {
            s_id = *it;
            c_s_ids.erase(s_id);
            SimpleCallEvent(CanTuio113D,removeTuioCursor3D,(s_id));
        }
    }

}

void InputGestureTuio113D::tuio3Dobj(ReceivedMessageArgumentStream & args)
{
        const char* cmd;
        args >> cmd;

        if(strcmp(cmd,"set")== 0)
        {

            int32 s_id, f_id;
            float xpos, ypos, zpos, aangle, bangle, cangle , xspeed, yspeed, zspeed, aspeed,bspeed,cspeed, maccel, raccel;

            args >> s_id >> f_id >> xpos >> ypos >> zpos >> aangle >> bangle >> cangle >> xspeed >> yspeed >> zspeed >>  aspeed >> bspeed >>cspeed >> maccel >> raccel >> EndMessage;

            if(o_s_ids.find(s_id) == o_s_ids.end())
            {
                SimpleCallEvent(CanTuio113D,addTuioObject3D,(s_id, f_id,xpos, ypos, zpos, aangle, bangle, cangle , xspeed, yspeed, zspeed, aspeed,bspeed,cspeed, maccel, raccel));
                o_s_ids.insert(s_id);
            }
            else
            {
                SimpleCallEvent(CanTuio113D,updateTuioObject3D,(s_id, f_id,xpos, ypos, zpos, aangle, bangle, cangle , xspeed, yspeed, zspeed, aspeed,bspeed,cspeed, maccel, raccel));
            }

        }
        else if( strcmp( cmd, "alive" ) == 0 )
        {

            int32 s_id;
            std::set<int32> t(o_s_ids);
            while(!args.Eos())
            {
                args >> s_id;
                t.erase(s_id);
            }
            args >> EndMessage;
            for (std::set<int32>::iterator it = t.begin(); it != t.end(); ++it)
            {
                s_id = *it;
                o_s_ids.erase(s_id);
                SimpleCallEvent(CanTuio113D,removeTuioObject3D,(s_id));
            }
        }
}


}
