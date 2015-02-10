/*

    ofxTableGestures (formerly OF-TangibleFramework)
    Developed for Taller de Sistemes Interactius I
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

#include "InputGestureTuio1.12.5D.hpp"
#include <string>

ofEvent<InputGestureTuio1125D::addTuioCursor25DArgs> InputGestureTuio1125D::addTuioCursor25D;
ofEvent<InputGestureTuio1125D::updateTuioCursor25DArgs> InputGestureTuio1125D::updateTuioCursor25D;
ofEvent<InputGestureTuio1125D::removeTuioCursor25DArgs> InputGestureTuio1125D::removeTuioCursor25D;
ofEvent<InputGestureTuio1125D::addTuioObject25DArgs> InputGestureTuio1125D::addTuioObject25D;
ofEvent<InputGestureTuio1125D::updateTuioObject25DArgs> InputGestureTuio1125D::updateTuioObject25D;
ofEvent<InputGestureTuio1125D::removeTuioObject25DArgs> InputGestureTuio1125D::removeTuioObject25D;
ofEvent<InputGestureTuio1125D::addTuioBlob25DArgs> InputGestureTuio1125D::addTuioBlob25D;
ofEvent<InputGestureTuio1125D::updateTuioBlob25DArgs> InputGestureTuio1125D::updateTuioBlob25D;
ofEvent<InputGestureTuio1125D::removeTuioBlob25DArgs> InputGestureTuio1125D::removeTuioBlob25D;

void InputGestureTuio1125D::ReceiveCall(OscInput::EventNewOscMessageArgs & args)
{
    std::string addr = args.m.getAddress();
    OscOptionalUnpacker uargs(args.m);

    if( addr == "/tuio/25Dcur" )
        tuio25Dcur(uargs);
    if( addr == "/tuio/25Dobj" )
        tuio25Dobj(uargs);
    if( addr == "/tuio/25Dblb" )
        tuio25Dobj(uargs);

}

void InputGestureTuio1125D::tuio25Dcur(OscOptionalUnpacker & args)
{
    std::string cmd;
    args >> cmd;

    if(cmd =="set")
    {
        int s_id;
        float xpos(0), ypos(0), zpos(0), xspeed(0), yspeed(0), zspeed(0), maccel(0);

        args >> s_id >> xpos >> ypos >> zpos >> xspeed >> yspeed >> zspeed >> maccel ;

        if(c_s_ids.find(s_id) == c_s_ids.end())
        {
            addTuioCursor25DArgs eventargs;
            eventargs.id = s_id;
            eventargs.xpos = xpos;
            eventargs. ypos =  ypos;
            eventargs. zpos =  zpos;
            eventargs. xspeed =  xspeed;
            eventargs. yspeed =  yspeed;
            eventargs. zspeed =  zspeed;
            eventargs. maccel =  maccel;
            ofNotifyEvent(addTuioCursor25D,eventargs);

            c_s_ids.insert(s_id);
        }
        else
        {
            updateTuioCursor25DArgs eventargs;
            eventargs.id = s_id;
            eventargs.xpos = xpos;
            eventargs. ypos =  ypos;
            eventargs. zpos =  zpos;
            eventargs. xspeed =  xspeed;
            eventargs. yspeed =  yspeed;
            eventargs. zspeed =  zspeed;
            eventargs. maccel =  maccel;
            ofNotifyEvent(updateTuioCursor25D,eventargs);

        }

    }
    else if(  cmd== "alive"  )
    {
        int s_id=0;
        std::set<int> t(c_s_ids);
        while(!args.Eos())
        {
            args >> s_id;
            t.erase(s_id);
        }

        for (std::set<int>::iterator it = t.begin(); it != t.end(); ++it)
        {
            s_id = *it;
            c_s_ids.erase(s_id);
            removeTuioCursor25DArgs eventargs;
            eventargs.id = s_id;
            ofNotifyEvent(removeTuioCursor25D,eventargs);

        }
    }

}

void InputGestureTuio1125D::tuio25Dobj(OscOptionalUnpacker & args)
{
    std::string cmd;
    args >> cmd;

    if(cmd=="set")
    {

        int s_id=0, f_id=0;
        float xpos=0, ypos=0, zpos=0, angle=0, xspeed=0, yspeed=0, zspeed=0, rspeed=0, maccel=0, raccel=0;

        args >> s_id >> f_id >> xpos >> ypos >> zpos >> angle >> xspeed >> yspeed >> zspeed >> rspeed >> maccel >> raccel ;

        if(o_s_ids.find(s_id) == o_s_ids.end())
        {
            addTuioObject25DArgs eventargs;
            eventargs.id = s_id;
            eventargs.f_id = f_id;
            eventargs.xpos = xpos;
            eventargs. ypos =  ypos;
            eventargs. zpos =  zpos;
            eventargs. angle =  angle;
            eventargs. xspeed =  xspeed;
            eventargs. yspeed =  yspeed;
            eventargs. zspeed =  zspeed;
            eventargs. rspeed =  rspeed;
            eventargs. maccel =  maccel;
            eventargs. raccel =  raccel;
            ofNotifyEvent(addTuioObject25D,eventargs);

            o_s_ids.insert(s_id);
        }
        else
        {
            updateTuioObject25DArgs eventargs;
            eventargs.id = s_id;
            eventargs.f_id = f_id;
            eventargs.xpos = xpos;
            eventargs. ypos =  ypos;
            eventargs. zpos =  zpos;
            eventargs. angle =  angle;
            eventargs. xspeed =  xspeed;
            eventargs. yspeed =  yspeed;
            eventargs. zspeed =  zspeed;
            eventargs. rspeed =  rspeed;
            eventargs. maccel =  maccel;
            eventargs. raccel =  raccel;
            ofNotifyEvent(updateTuioObject25D,eventargs);

        }

    }
    else if(  cmd == "alive"  )
    {

        int s_id=0;
        std::set<int> t(o_s_ids);
        while(!args.Eos())
        {
            args >> s_id;
            t.erase(s_id);
        }

        for (std::set<int>::iterator it = t.begin(); it != t.end(); ++it)
        {
            s_id = *it;
            o_s_ids.erase(s_id);
            removeTuioObject25DArgs eventargs;
            eventargs.id = s_id;
            ofNotifyEvent(removeTuioObject25D,eventargs);

        }
    }
}

void InputGestureTuio1125D::tuio25Dblb(OscOptionalUnpacker & args)
{
    std::string cmd;
    args >> cmd;

    if(cmd=="set")
    {

        int s_id;
        float xpos=0, ypos=0, zpos=0, angle=0, width=0, height=0, area=0, xspeed=0, yspeed=0, zspeed=0, rspeed=0, maccel=0, raccel=0;

        args >> s_id >> xpos >> ypos >> zpos >> angle >> width >> height >> area >> xspeed >> yspeed >> zspeed >> rspeed >> maccel >> raccel ;

        if(b_s_ids.find(s_id) == b_s_ids.end())
        {
            addTuioBlob25DArgs eventargs;
            eventargs.id = s_id;
            eventargs.xpos = xpos;
            eventargs. ypos =  ypos;
            eventargs. zpos =  zpos;
            eventargs. angle =  angle;
            eventargs. width =  width;
            eventargs. height =  height;
            eventargs. area =  area;
            eventargs. xspeed =  xspeed;
            eventargs. yspeed =  yspeed;
            eventargs. zspeed =  zspeed;
            eventargs. rspeed =  rspeed;
            eventargs. maccel =  maccel;
            eventargs. raccel =  raccel;
            ofNotifyEvent(addTuioBlob25D,eventargs);

            b_s_ids.insert(s_id);
        }
        else
        {
            updateTuioBlob25DArgs eventargs;
            eventargs.id = s_id;
            eventargs.xpos = xpos;
            eventargs. ypos =  ypos;
            eventargs. zpos =  zpos;
            eventargs. angle =  angle;
            eventargs. width =  width;
            eventargs. height =  height;
            eventargs. area =  area;
            eventargs. xspeed =  xspeed;
            eventargs. yspeed =  yspeed;
            eventargs. zspeed =  zspeed;
            eventargs. rspeed =  rspeed;
            eventargs. maccel =  maccel;
            eventargs. raccel =  raccel;
            ofNotifyEvent(updateTuioBlob25D,eventargs);

        }

    }
    else if( cmd == "alive"  )
    {

        int s_id=0;
        std::set<int> t(b_s_ids);
        while(!args.Eos())
        {
            args >> s_id;
            t.erase(s_id);
        }

        for (std::set<int>::iterator it = t.begin(); it != t.end(); ++it)
        {
            s_id = *it;
            b_s_ids.erase(s_id);
            removeTuioBlob25DArgs eventargs;
            eventargs.id = s_id;
            ofNotifyEvent(removeTuioBlob25D,eventargs);

        }
    }
}

