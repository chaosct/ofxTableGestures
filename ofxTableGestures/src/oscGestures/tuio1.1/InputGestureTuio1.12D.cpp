#include "tuio1.1/InputGestureTuio1.12D.hpp"

#include <cstring>

using namespace osc;

namespace tuio
{

void InputGestureTuio112D::ReceiveCall(const char * addr, ReceivedMessageArgumentStream & args)
{
    if(!valid)
        return;
    if( strcmp( addr, "/tuio/2Dcur" ) == 0 )
        tuio2Dcur(args);
    if( strcmp( addr, "/tuio/2Dobj" ) == 0 )
        tuio2Dobj(args);
    if( strcmp( addr, "/tuio/2Dblb" ) == 0 )
        tuio2Dobj(args);
}

void InputGestureTuio112D::tuio2Dcur(ReceivedMessageArgumentStream & args)
{
    const char* cmd;
    args >> cmd;

    if(strcmp(cmd,"set")== 0)
    {
        int32 s_id;
        float xpos, ypos, xspeed, yspeed, maccel;

        args >> s_id >> xpos >> ypos >> xspeed >> yspeed >> maccel >> EndMessage;

        if(c_s_ids.find(s_id) == c_s_ids.end())
        {
            if(checkCursorLimits)
            {
                float newxpos = (xpos -0.125f)*1.33f;
                float dx = newxpos - 0.5;
                float dy = ypos -0.5;
                float d = sqrt(dx*dx+dy*dy);
                if(d > 0.5)
                {
                    std::cout << "Ignoring finger in " << xpos << "," << ypos << std::endl;
                    return;
                }
            }

            TeventTuio11NewFinger2D * e = new TeventTuio11NewFinger2D();
            e->s_id = s_id;
            e->xpos = xpos;
            e->ypos = ypos;
            e->xspeed = xspeed;
            e->yspeed = yspeed;
            e->maccel = maccel;
            events.push_back(e);
            c_s_ids.insert(s_id);
        }
        else
        {

            TeventTuio11MoveFinger2D * e = new TeventTuio11MoveFinger2D();
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
            TeventTuio11RemoveFinger2D * e = new TeventTuio11RemoveFinger2D();
            e->s_id = s_id;
            events.push_back(e);
        }
    }

}

void InputGestureTuio112D::tuio2Dobj(ReceivedMessageArgumentStream & args)
{
           const char* cmd;
        args >> cmd;

        if(strcmp(cmd,"set")== 0)
        {
            int32 s_id, f_id;
            float xpos, ypos, angle, xspeed, yspeed, rspeed, maccel, raccel;

            args >> s_id >> f_id >> xpos >> ypos >> angle >> xspeed >> yspeed >> rspeed >> maccel >> raccel >> EndMessage;

            if(o_s_ids.find(s_id) == o_s_ids.end())
            {
                if(checkObjectLimits)
                {
                    float newxpos = (xpos -0.125f)*1.33f;
                    float dx = newxpos - 0.5;
                    float dy = ypos -0.5;
                    float d = sqrt(dx*dx+dy*dy);
                    if(d > 0.5)
                    {
                        std::cout << "Ignoring object in " << xpos << "," << ypos << std::endl;
                        return;
                    }
                }

                TeventTuio11NewObject2D * e = new TeventTuio11NewObject2D();
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
                o_s_ids.insert(s_id);
            }
            else
            {

                TeventTuio11MoveObject2D * e = new TeventTuio11MoveObject2D();
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
                TeventTuio11RemoveObject2D * e = new TeventTuio11RemoveObject2D();
                e->s_id = s_id;
                events.push_back(e);
            }
        }

}

void InputGestureTuio112D::tuio2Dblb(ReceivedMessageArgumentStream & args)
{
           const char* cmd;
        args >> cmd;

        if(strcmp(cmd,"set")== 0)
        {
            int32 s_id;
            float xpos, ypos, angle, width, height, area, xspeed, yspeed, rspeed, maccel, raccel;
            args >> s_id >> xpos >> ypos >> angle >> width >> height >> area >> xspeed >> yspeed >> rspeed >> maccel >> raccel >> EndMessage;

            if(b_s_ids.find(s_id) == b_s_ids.end())
            {

                TeventTuio11NewBlob2D * e = new TeventTuio11NewBlob2D();
                e->s_id = s_id;
                e->xpos = xpos;
                e->ypos = ypos;
                e->angle = angle;
                e->width = width;
                e->height = height;
                e->area = area;
                e->xspeed = xspeed;
                e->yspeed = yspeed;
                e->rspeed = rspeed;
                e->maccel = maccel;
                e->raccel = raccel;
                events.push_back(e);
                b_s_ids.insert(s_id);
            }
            else
            {

                TeventTuio11MoveBlob2D * e = new TeventTuio11MoveBlob2D();
                e->s_id = s_id;
                e->xpos = xpos;
                e->ypos = ypos;
                e->angle = angle;
                e->width = width;
                e->height = height;
                e->area = area;
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

            int32 s_id;
            std::set<int32> t(b_s_ids);
            while(!args.Eos())
            {
                args >> s_id;
                t.erase(s_id);
            }
            args >> EndMessage;
            for (std::set<int32>::iterator it = t.begin(); it != t.end(); ++it)
            {
                s_id = *it;
                b_s_ids.erase(s_id);
                TeventTuio11RemoveBlob2D * e = new TeventTuio11RemoveBlob2D();
                e->s_id = s_id;
                events.push_back(e);
            }
        }

}



}
