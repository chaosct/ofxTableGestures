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

#include "InputGestureTuio1.13D.hpp"
#include <string>

ofEvent<InputGestureTuio113D::addTuioCursor3DArgs> InputGestureTuio113D::addTuioCursor3D;
ofEvent<InputGestureTuio113D::updateTuioCursor3DArgs> InputGestureTuio113D::updateTuioCursor3D;
ofEvent<InputGestureTuio113D::removeTuioCursor3DArgs> InputGestureTuio113D::removeTuioCursor3D;
ofEvent<InputGestureTuio113D::addTuioObject3DArgs> InputGestureTuio113D::addTuioObject3D;
ofEvent<InputGestureTuio113D::updateTuioObject3DArgs> InputGestureTuio113D::updateTuioObject3D;
ofEvent<InputGestureTuio113D::removeTuioObject3DArgs> InputGestureTuio113D::removeTuioObject3D;

void InputGestureTuio113D::ReceiveCall(OscInput::EventNewOscMessageArgs & args)
{
    std::string addr = args.m.getAddress();
    OscOptionalUnpacker uargs(args.m);

    if( addr == "/tuio/3Dcur" )
        tuio3Dcur(uargs);
    if( addr == "/tuio/3Dobj" )
        tuio3Dobj(uargs);
    if( addr == "/tuio/3Dblb" )
        tuio3Dobj(uargs);

}

void InputGestureTuio113D::tuio3Dcur(OscOptionalUnpacker & args)
{
    std::string cmd;
    args >> cmd;

    if(cmd == "set")
    {
        int s_id;
        float xpos=0, ypos=0, zpos=0, xspeed=0, yspeed=0, zspeed=0, maccel=0;

        args >> s_id >> xpos >> ypos >> zpos >> xspeed >> yspeed >> zspeed >> maccel ;

        if(c_s_ids.find(s_id) == c_s_ids.end())
        {
            addTuioCursor3DArgs eventargs;
            eventargs.id = s_id;
            eventargs. xpos =  xpos;
            eventargs. ypos =  ypos;
            eventargs. zpos =  zpos;
            eventargs. xspeed =  xspeed;
            eventargs. yspeed =  yspeed;
            eventargs. zspeed =  zspeed;
            eventargs. maccel =  maccel;
            ofNotifyEvent(addTuioCursor3D,eventargs);

            c_s_ids.insert(s_id);
        }
        else
        {
            updateTuioCursor3DArgs eventargs;
            eventargs.id = s_id;
            eventargs. xpos =  xpos;
            eventargs. ypos =  ypos;
            eventargs. zpos =  zpos;
            eventargs. xspeed =  xspeed;
            eventargs. yspeed =  yspeed;
            eventargs. zspeed =  zspeed;
            eventargs. maccel =  maccel;
            ofNotifyEvent(updateTuioCursor3D,eventargs);

        }

    }
    else if( cmd == "alive" )
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
            removeTuioCursor3DArgs eventargs;
            eventargs.id = s_id;
            ofNotifyEvent(removeTuioCursor3D,eventargs);

        }
    }

}

void InputGestureTuio113D::tuio3Dobj(OscOptionalUnpacker & args)
{
    std::string cmd;
    args >> cmd;

    if(cmd == "set")
    {

        int s_id=0, f_id=0;
        float xpos=0, ypos=0, zpos=0, aangle=0, bangle=0, cangle =0, xspeed=0, yspeed=0, zspeed=0, aspeed=0,bspeed=0,cspeed=0, maccel=0, raccel=0;

        args >> s_id >> f_id >> xpos >> ypos >> zpos >> aangle >> bangle >> cangle >> xspeed >> yspeed >> zspeed >>  aspeed >> bspeed >>cspeed >> maccel >> raccel ;

        if(o_s_ids.find(s_id) == o_s_ids.end())
        {
            addTuioObject3DArgs eventargs;
            eventargs.id = s_id;
            eventargs. f_id =  f_id;
            eventargs.xpos = xpos;
            eventargs. ypos =  ypos;
            eventargs. zpos =  zpos;
            eventargs. aangle =  aangle;
            eventargs. bangle =  bangle;
            eventargs. cangle  =  cangle ;
            eventargs. xspeed =  xspeed;
            eventargs. yspeed =  yspeed;
            eventargs. zspeed =  zspeed;
            eventargs. aspeed =  aspeed;
            eventargs.bspeed = bspeed;
            eventargs.cspeed = cspeed;
            eventargs. maccel =  maccel;
            eventargs. raccel =  raccel;
            ofNotifyEvent(addTuioObject3D,eventargs);

            o_s_ids.insert(s_id);
        }
        else
        {
            updateTuioObject3DArgs eventargs;
            eventargs.id = s_id;
            eventargs. f_id =  f_id;
            eventargs.xpos = xpos;
            eventargs. ypos =  ypos;
            eventargs. zpos =  zpos;
            eventargs. aangle =  aangle;
            eventargs. bangle =  bangle;
            eventargs. cangle  =  cangle ;
            eventargs. xspeed =  xspeed;
            eventargs. yspeed =  yspeed;
            eventargs. zspeed =  zspeed;
            eventargs. aspeed =  aspeed;
            eventargs.bspeed = bspeed;
            eventargs.cspeed = cspeed;
            eventargs. maccel =  maccel;
            eventargs. raccel =  raccel;
            ofNotifyEvent(updateTuioObject3D,eventargs);

        }

    }
    else if(cmd == "alive" )
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
            removeTuioObject3DArgs eventargs;
            eventargs.id = s_id;
            ofNotifyEvent(removeTuioObject3D,eventargs);

        }
    }
}



