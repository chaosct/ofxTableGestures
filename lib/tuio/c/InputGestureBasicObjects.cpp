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
#include "InputGestureBasicObjects.h"

#include <iostream>
#include <cstring>

namespace tuio {


bool InputGestureBasicObjects::active = false;

void InputGestureBasicObjects::ReceiveCall(const char * addr, osc::ReceivedMessageArgumentStream & args)
{
    if(!active) return;
    if( strcmp( addr, "/tuio/2Dobj" ) == 0 )
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
            int32 s_id, f_id;
            float xpos, ypos, angle, xspeed, yspeed, rspeed, maccel, raccel;

            args >> s_id >> f_id >> xpos >> ypos >> angle >> xspeed >> yspeed >> rspeed >> maccel >> raccel >> EndMessage;

            if(s_ids.find(s_id) == s_ids.end())
            {

                TeventBasicObjectsNewObject * e = new TeventBasicObjectsNewObject();
                e->s_id = s_id;
                e->f_id = f_id;
                e->xpos = xpos;
                e->ypos = ypos;
                e->angle = angle;
                e->xspeed = xspeed;
                e->yspeed = yspeed;
                e->rspeed = rspeed;
                e->maccel = maccel;
                e->raccel = raccel;
                events.push_back(e);
                s_ids.insert(s_id);
            }
            else
            {

                TeventBasicObjectsMoveObject * e = new TeventBasicObjectsMoveObject();
                e->s_id = s_id;
                e->f_id = f_id;
                e->xpos = xpos;
                e->ypos = ypos;
                e->angle = angle;
                e->xspeed = xspeed;
                e->yspeed = yspeed;
                e->rspeed = rspeed;
                e->maccel = maccel;
                e->raccel = raccel;
                events.push_back(e);
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
            std::set<int32> t(s_ids);
            while(!args.Eos())
            {
                args >> s_id;
                t.erase(s_id);
            }
            args >> EndMessage;
            for (std::set<int32>::iterator it = t.begin(); it != t.end(); it++)
            {
                s_id = *it;
                s_ids.erase(s_id);
                TeventBasicObjectsRemoveObject * e = new TeventBasicObjectsRemoveObject();
                e->s_id = s_id;
                events.push_back(e);
            }
        }
        else if( strcmp(cmd,"fseq") == 0)
        {
            lastFrame = currentFrame;
            args >> currentFrame  >> EndMessage;
            //std::cout << "frame " << currentFrame << std::endl;
        }
        else
        {

            std::cout << "Unkwnown command in  : /tuio/2Dobj" << cmd << std::endl;

        }


    }
}



} // namespace tuio
