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
#include "InputGestureDirectFingers.h"
#include <cstring>

namespace tuio
{


void InputGestureDirectFingers::ReceiveCall(const char * addr, osc::ReceivedMessageArgumentStream & args)
{
    if( strcmp( addr, "/tuio/2Dcur" ) == 0 )
    {

        const char* cmd;
        args >> cmd;

        if(strcmp(cmd,"set")== 0)
        {
            if (currentFrame<lastFrame)
            {
                std::cout << "Frame dropped: " << currentFrame << "<" << lastFrame << std::endl;
                return;
            }
            int32 s_id;
            float xpos, ypos, xspeed, yspeed, maccel;

            args >> s_id >> xpos >> ypos >> xspeed >> yspeed >> maccel >> EndMessage;

            if(fingers.find(s_id) == fingers.end())
            {

                DirectFinger * e = new DirectFinger();
                e->s_id = s_id;
                e->xpos = xpos;
                e->ypos = ypos;
                e->xspeed = xspeed;
                e->yspeed = yspeed;
                e->maccel = maccel;
                fingers[s_id]=e;

                TeventDirectFingersNewFinger * evt = new TeventDirectFingersNewFinger();
                evt->s_id = s_id;
                evt->df = e;
                events.push_back(evt);

            }
            else
            {

                DirectFinger * e = fingers[s_id];
                e->s_id = s_id;
                e->xpos = xpos;
                e->ypos = ypos;
                e->xspeed = xspeed;
                e->yspeed = yspeed;
                e->maccel = maccel;
            }

        }
        else if( strcmp( cmd, "alive" ) == 0 )
        {
            if (currentFrame<lastFrame)
            {
                std::cout << "Frame dropped: " << currentFrame << "<" << lastFrame << std::endl;
                return;
            }
            int32 s_id;
            std::map<int32,DirectFinger *> t;
            while(!args.Eos())
            {
                args >> s_id;
                std::map<int32,DirectFinger *>::iterator it = fingers.find(s_id);
                if(it != fingers.end())
                {
                    t[s_id]=it->second;
                    fingers.erase(it);
                }
            }
            args >> EndMessage;
            for (std::map<int32,DirectFinger *>::iterator it = fingers.begin(); it != fingers.end(); ++it)
            {
                TeventDirectFingersRemoveFinger * evt = new TeventDirectFingersRemoveFinger();
                evt->s_id = it->first;
                events.push_back(evt);
                //delete it->second;
            }
            fingers = t;
        }
        else if( strcmp(cmd,"fseq") == 0)
        {
            lastFrame = currentFrame;
            args >> currentFrame  >> EndMessage;
            //std::cout << "frame " << currentFrame << std::endl;
        }
        else
        {

            std::cout << "Unkwnown command in  : /tuio/2Dcur" << cmd << std::endl;

        }


    }
}


}
