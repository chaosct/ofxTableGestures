#include "InputGestureBasicFingers.h"

#include <iostream>
#include <cstring>

namespace tuio
{

void InputGestureBasicFingers::ReceiveCall(const char * addr, osc::ReceivedMessageArgumentStream & args)
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

            if(s_ids.find(s_id) == s_ids.end())
            {

                TeventBasicFingersNewFinger * e = new TeventBasicFingersNewFinger();
                e->s_id = s_id;
                e->xpos = xpos;
                e->ypos = ypos;
                e->xspeed = xspeed;
                e->yspeed = yspeed;
                e->maccel = maccel;
                events.push_back(e);
                s_ids.insert(s_id);
            }
            else
            {

                TeventBasicFingersMoveFinger * e = new TeventBasicFingersMoveFinger();
                e->s_id = s_id;
                e->xpos = xpos;
                e->ypos = ypos;
                e->xspeed = xspeed;
                e->yspeed = yspeed;
                e->maccel = maccel;
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
                TeventBasicFingersRemoveFinger * e = new TeventBasicFingersRemoveFinger();
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

            std::cout << "Unkwnown command in  : /tuio/2Dcur" << cmd << std::endl;

        }


    }
}



} // namespace tuio
