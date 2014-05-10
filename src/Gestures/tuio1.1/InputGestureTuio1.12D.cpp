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

#include "InputGestureTuio1.12D.hpp"

#include <string>
#include "TableApp.hpp"


void InputGestureTuio112D::ReceiveCall(InputGestureOSC::EventNewOScMessageArgs & args)
{
    std::string addr = args.m.getAddress();
    OscOptionalUnpacker uargs(args.m);

    if( addr == "/tuio/2Dcur" )
        tuio2Dcur(uargs);
    if( addr == "/tuio/2Dobj" )
        tuio2Dobj(uargs);
    if( addr == "/tuio/2Dblb" )
        tuio2Dobj(uargs);
}

void InputGestureTuio112D::tuio2Dcur(OscOptionalUnpacker & args)
{
    std::string cmd;
    args >> cmd;

    if(cmd=="set")
    {
        int s_id;
        float xpos=0, ypos=0, xspeed=0, yspeed=0, maccel=0;

        args >> s_id >> xpos >> ypos >> xspeed >> yspeed >> maccel ;

        ///We definetively need a different way to specify this (a parameter for tuio aspect ratio?)
        if(squaredInterface)
        {
            float mins = min(ofGetWidth(),ofGetHeight());
            float w = ofGetWidth()/mins;
            float h = ofGetHeight()/mins;
            xpos = xpos * w - (w-1)/2;
            ypos = ypos * h - (h-1)/2;
            if (limitroundarea && sqrt((xpos-0.5f)*(xpos-0.5f)+(ypos-0.5f)*(ypos-0.5f)) > 0.5f)
            {
                return;
            }
        }
        else
        {
            ypos = ypos * TableApp::getHeight();
            xpos = xpos * TableApp::getWidth();
        }
        
        if(c_s_ids.find(s_id) == c_s_ids.end())
        {
            addTuioCursor2DArgs eventargs;
            eventargs.id = s_id;
            eventargs. xpos =  xpos;
            eventargs.ypos = ypos;
            eventargs.xspeed = xspeed;
            eventargs.yspeed = yspeed;
            eventargs.maccel  = maccel ;
            ofNotifyEvent(addTuioCursor2D,eventargs);

            c_s_ids.insert(s_id);
        }
        else
        {

            updateTuioCursor2DArgs eventargs;
            eventargs.id = s_id;
            eventargs. xpos =  xpos;
            eventargs.ypos = ypos;
            eventargs.xspeed = xspeed;
            eventargs.yspeed = yspeed;
            eventargs.maccel  = maccel ;
            ofNotifyEvent(updateTuioCursor2D,eventargs);

        }

    }
    else if( cmd== "alive"  )
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
            removeTuioCursor2DArgs eventargs;
            eventargs.id = s_id;
            ofNotifyEvent(removeTuioCursor2D,eventargs);

        }
    }

}

void InputGestureTuio112D::tuio2Dobj(OscOptionalUnpacker & args)
{
    std::string cmd;
    args >> cmd;

    if(cmd=="set")
    {
        int s_id=0, f_id=0;
        float xpos=0, ypos=0, angle=0, xspeed=0, yspeed=0, rspeed=0, maccel=0, raccel=0;

        args >> s_id >> f_id >> xpos >> ypos >> angle >> xspeed >> yspeed >> rspeed >> maccel >> raccel ;

        ///We definetively need a different way to specify this (a parameter for tuio aspect ratio?)
        if(squaredInterface)
        {
            float mins = min(ofGetWidth(),ofGetHeight());
            float w = ofGetWidth()/mins;
            float h = ofGetHeight()/mins;
            xpos = xpos * w - (w-1)/2;
            ypos = ypos * h - (h-1)/2;
            if (limitroundareaobj && sqrt((xpos-0.5f)*(xpos-0.5f)+(ypos-0.5f)*(ypos-0.5f)) > 0.5f)
            {
                return;
            }
        }
        else
        {
            ypos = ypos * TableApp::getHeight();
            xpos = xpos * TableApp::getWidth();
        }
        if(o_s_ids.find(s_id) == o_s_ids.end())
        {
            o_s_ids.insert(s_id);
            addTuioObject2DArgs eventargs;
            eventargs.id =  s_id;
            eventargs. f_id  =  f_id ;
            eventargs.xpos = xpos;
            eventargs. ypos =  ypos;
            eventargs. angle =  angle;
            eventargs. xspeed =  xspeed;
            eventargs.yspeed = yspeed;
            eventargs. rspeed =  rspeed;
            eventargs. maccel =  maccel;
            eventargs.  raccel =   raccel;
            ofNotifyEvent(addTuioObject2D,eventargs);

        }
        else
        {
            updateTuioObject2DArgs eventargs;
            eventargs. id =  s_id;
            eventargs. f_id  =  f_id ;
            eventargs.xpos = xpos;
            eventargs. ypos =  ypos;
            eventargs. angle =  angle;
            eventargs. xspeed =  xspeed;
            eventargs.yspeed = yspeed;
            eventargs. rspeed =  rspeed;
            eventargs. maccel =  maccel;
            eventargs.  raccel =   raccel;
            ofNotifyEvent(updateTuioObject2D,eventargs);

        }

    }
    else if( cmd == "alive"  )
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
            removeTuioObject2DArgs eventargs;
            eventargs.id = s_id;
            ofNotifyEvent(removeTuioObject2D,eventargs);

        }
    }

}

void InputGestureTuio112D::tuio2Dblb(OscOptionalUnpacker & args)
{
    std::string cmd;
    args >> cmd;

    if(cmd=="set")
    {
        int s_id;
        float xpos=0, ypos=0, angle=0, width=0, height=0, area=0, xspeed=0, yspeed=0, rspeed=0, maccel=0, raccel=0;
        args >> s_id >> xpos >> ypos >> angle >> width >> height >> area >> xspeed >> yspeed >> rspeed >> maccel >> raccel ;

        if(b_s_ids.find(s_id) == b_s_ids.end())
        {
            addTuioBlob2DArgs eventargs;
            eventargs.id = s_id;
            eventargs.xpos =  xpos;
            eventargs.ypos =  ypos;
            eventargs.angle =   angle;
            eventargs.width =   width;
            eventargs.height =   height;
            eventargs.  area =   area;
            eventargs.  xspeed =   xspeed;
            eventargs. yspeed =  yspeed;
            eventargs. rspeed =  rspeed;
            eventargs. maccel =  maccel;
            eventargs.  raccel =   raccel;
            ofNotifyEvent(addTuioBlob2D,eventargs);

            b_s_ids.insert(s_id);
        }
        else
        {
            updateTuioBlob2DArgs eventargs;
            eventargs.id = s_id;
            eventargs. xpos =  xpos;
            eventargs. ypos =  ypos;
            eventargs.  angle =   angle;
            eventargs.  width =   width;
            eventargs.  height =   height;
            eventargs.  area =   area;
            eventargs.  xspeed =   xspeed;
            eventargs. yspeed =  yspeed;
            eventargs. rspeed =  rspeed;
            eventargs. maccel =  maccel;
            eventargs.  raccel =   raccel;
            ofNotifyEvent(updateTuioBlob2D,eventargs);

        }

    }
    else if(  cmd == "alive"  )
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
            removeTuioBlob2DArgs eventargs;
            eventargs.id = s_id;
            ofNotifyEvent(removeTuioBlob2D,eventargs);

        }
    }

}
