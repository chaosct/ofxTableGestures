#include "tuio1.1/InputGestureTuio1.12.5D.h"
#include <cstring>

using namespace osc;

namespace tuio
{

void InputGestureTuio1125D::ReceiveCall(const char * addr, ReceivedMessageArgumentStream & args)
{
    if(!valid)
        return;
    if( strcmp( addr, "/tuio/25Dcur" ) == 0 )
        tuio25Dcur(args);
    if( strcmp( addr, "/tuio/25Dobj" ) == 0 )
        tuio25Dobj(args);
    if( strcmp( addr, "/tuio/25Dblb" ) == 0 )
        tuio25Dblb(args);
}

void InputGestureTuio1125D::tuio25Dcur(ReceivedMessageArgumentStream & args)
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

            TeventTuio11NewFinger25D * e = new TeventTuio11NewFinger25D();
            e->s_id = s_id;
            e->xpos = xpos;
            e->ypos = ypos;
            e->zpos = zpos;
            e->xspeed = xspeed;
            e->yspeed = yspeed;
            e->zspeed = zspeed;
            e->maccel = maccel;
            events.push_back(e);
            c_s_ids.insert(s_id);
        }
        else
        {

            TeventTuio11MoveFinger25D * e = new TeventTuio11MoveFinger25D();
            e->s_id = s_id;
            e->xpos = xpos;
            e->ypos = ypos;
            e->zpos = zpos;
            e->xspeed = xspeed;
            e->yspeed = yspeed;
            e->zspeed = zspeed;
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
            TeventTuio11RemoveFinger25D * e = new TeventTuio11RemoveFinger25D();
            e->s_id = s_id;
            events.push_back(e);
        }
    }

}

void InputGestureTuio1125D::tuio25Dobj(ReceivedMessageArgumentStream & args)
{
           const char* cmd;
        args >> cmd;

        if(strcmp(cmd,"set")== 0)
        {

            int32 s_id, f_id;
            float xpos, ypos, zpos, angle, xspeed, yspeed, zspeed, rspeed, maccel, raccel;

            args >> s_id >> f_id >> xpos >> ypos >> zpos >> angle >> xspeed >> yspeed >> zspeed >> rspeed >> maccel >> raccel >> EndMessage;

            if(o_s_ids.find(s_id) == o_s_ids.end())
            {

                TeventTuio11NewObject25D * e = new TeventTuio11NewObject25D();
                e->s_id = s_id;
                e->f_id = f_id;
                e->xpos = xpos;
                e->ypos = ypos;
                e->zpos = zpos;
                e->angle = angle;
                e->xspeed = xspeed;
                e->yspeed = yspeed;
                e->zspeed = zspeed;
                e->rspeed = rspeed;
                e->maccel = maccel;
                e->raccel = raccel;
                events.push_back(e);
                o_s_ids.insert(s_id);
            }
            else
            {

                TeventTuio11MoveObject25D * e = new TeventTuio11MoveObject25D();
                e->s_id = s_id;
                e->f_id = f_id;
                e->xpos = xpos;
                e->ypos = ypos;
                e->zpos = zpos;
                e->angle = angle;
                e->xspeed = xspeed;
                e->yspeed = yspeed;
                e->zspeed = zspeed;
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
                TeventTuio11RemoveObject25D * e = new TeventTuio11RemoveObject25D();
                e->s_id = s_id;
                events.push_back(e);
            }
        }
}

void InputGestureTuio1125D::tuio25Dblb(ReceivedMessageArgumentStream & args)
{
           const char* cmd;
        args >> cmd;

        if(strcmp(cmd,"set")== 0)
        {

            int32 s_id;
            float xpos, ypos, zpos, angle, width, height, area, xspeed, yspeed, zspeed, rspeed, maccel, raccel;

            args >> s_id >> xpos >> ypos >> zpos >> angle >> width >> height >> area >> xspeed >> yspeed >> zspeed >> rspeed >> maccel >> raccel >> EndMessage;

            if(b_s_ids.find(s_id) == b_s_ids.end())
            {

                TeventTuio11NewBlob25D * e = new TeventTuio11NewBlob25D();
                e->s_id = s_id;
                e->xpos = xpos;
                e->ypos = ypos;
                e->zpos = zpos;
                e->angle = angle;
                e->width = width;
                e->height = height;
                e->area = area;
                e->xspeed = xspeed;
                e->yspeed = yspeed;
                e->zspeed = zspeed;
                e->rspeed = rspeed;
                e->maccel = maccel;
                e->raccel = raccel;
                events.push_back(e);
                b_s_ids.insert(s_id);
            }
            else
            {

                TeventTuio11MoveBlob25D * e = new TeventTuio11MoveBlob25D();
                e->s_id = s_id;
                e->xpos = xpos;
                e->ypos = ypos;
                e->zpos = zpos;
                e->angle = angle;
                e->width = width;
                e->height = height;
                e->area = area;
                e->xspeed = xspeed;
                e->yspeed = yspeed;
                e->zspeed = zspeed;
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
                TeventTuio11RemoveBlob25D * e = new TeventTuio11RemoveBlob25D();
                e->s_id = s_id;
                events.push_back(e);
            }
        }
}

}
