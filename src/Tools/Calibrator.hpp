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

#ifndef CALIBRATOR_HPP_INCLUDED
#define CALIBRATOR_HPP_INCLUDED

#include "Graphic.hpp"
#include "GlobalConfig.hpp"
#include "InputGestureLongPush.hpp"
#include "LongPushFeedback.hpp"

class Calibrator : public OnTable< tuio::CanLongPush< Graphic > >
{
    enum STATE {CENTER, ANGLE , ANGLE_W, ANGLE_H, SIZE, DONE}State;
    int STATE_ANGLE_W;
    int STATE_ANGLE_H;
    float & MAX_CENTER_DISTANCE;
    float & MAX_ANGLE_DISTANCE;
    float & MAX_SIZE_DISTORTION;
    float & MAX_ANGLE_DISTORTION;
    LongPushFeedback * lpf;
    public:
    Calibrator():
        MAX_CENTER_DISTANCE(GlobalConfig::getRef("TOOLS:CALIBRATOR:MAX_CENTER_DISTANCE",0.003f)),
        MAX_ANGLE_DISTANCE(GlobalConfig::getRef("TOOLS:CALIBRATOR:MAX_ANGLE_DISTANCE",1.0f)),
        MAX_SIZE_DISTORTION(GlobalConfig::getRef("TOOLS:CALIBRATOR:MAX_SIZE_DISTORTION",0.01f)),
        MAX_ANGLE_DISTORTION(GlobalConfig::getRef("TOOLS:CALIBRATOR:MAX_ANGLE_DISTORTION",0.01f)),
        lpf(NULL)
        {
            Activate();
        }
    void Activate()
    {
        State=CENTER;
        lpf = new LongPushFeedback();
    }
    void Deactivate()
    {
        State = DONE;
        if(lpf) delete lpf;
        lpf = NULL;
    }
    void draw()
    {
        switch (State)
        {
            #define _DrawCase(name) \
            case name:\
                draw##name();\
            break;

            _DrawCase(CENTER)
            _DrawCase(ANGLE)
            _DrawCase(SIZE)
            _DrawCase(ANGLE_W)
            _DrawCase(ANGLE_H)

            #undef _DrawCase

        }
    }
    //CanTap
    void LongPushTriger(float x, float y)
    {
        switch (State)
        {
            #define _TapCase(name) \
            case name:\
                Tap##name(x,y);\
            break;

            _TapCase(CENTER)
            _TapCase(ANGLE)
            _TapCase(SIZE)
            _TapCase(ANGLE_W)
            _TapCase(ANGLE_H)

            #undef _TapCase
        }

    }

    void drawCENTER()
    {
        ofSetColor(0,0,255);
        ofCircle(0.5,0.5,0.01);
    }
    void TapCENTER(float x, float y)
    {
        float dx= x-0.5;
        float dy= y-0.5;
        if (abs(dx) < MAX_CENTER_DISTANCE && abs(dy) < MAX_CENTER_DISTANCE)
        {
            State=ANGLE;
            return;
        }
        Renderer::center_x -= dx*ofGetWidth()/2;
        Renderer::center_y -= dy*ofGetHeight()/2;
    }

    void drawANGLE()
    {
        ofSetColor(0,0,255);
        ofLine(0.5,0.5,0.5,0);
    }
    void TapANGLE(float x, float y)
    {
        float angle = DirectPoint(0.5,0.5).getAngle(DirectPoint(x,y))*180.f/M_PI +90.0f;
        if (abs(angle) < MAX_ANGLE_DISTANCE)
        {
            State=ANGLE_W;
            STATE_ANGLE_W=0;
            return;
        }
        Renderer::angle -= angle;
    }

    void drawANGLE_W()
    {
        if(STATE_ANGLE_W == 0)
        {
            ofSetColor(0,0,255);
            ofCircle(0.2,0.5,0.01);
        }
        else
        {
            ofSetColor(0,0,255);
            ofCircle(0.8,0.5,0.01);
        }
    }

    void TapANGLE_W(float x,float y)
    {
        static bool first = true;
        static float lastx= 0;
        static float lessthanx = 45;
        static float morethanx = -45;
        if(!first and STATE_ANGLE_W == 1)
        {
            float dx = abs((x-0.5)/(lastx-0.5));
            if (abs(dx-1) < MAX_ANGLE_DISTORTION )
            {
                State=ANGLE_H;
                STATE_ANGLE_H=0;
                return;
            }
            if(dx < 1)
            {
                 lessthanx = Renderer::angle_w;
            }
            else if(dx > 1)
            {
                morethanx = Renderer::angle_w;
            }

            Renderer::angle_w = (morethanx + lessthanx) / 2;
        }
        first = false;
        lastx = x;
        STATE_ANGLE_W = ++STATE_ANGLE_W % 2;
    }

        void drawANGLE_H()
    {
        if(STATE_ANGLE_H == 0)
        {
            ofSetColor(0,0,255);
            ofCircle(0.5,0.2,0.01);
        }
        else
        {
            ofSetColor(0,0,255);
            ofCircle(0.5,0.8,0.01);
        }
    }

    void TapANGLE_H(float x,float y)
    {
        static bool first = true;
        static float lasty = 0;
        static float lessthany = 45;
        static float morethany = -45;
        if(!first and STATE_ANGLE_H == 1)
        {
            float dy = abs((y-0.5)/(lasty-0.5));
            if ( abs(dy-1) < MAX_ANGLE_DISTORTION)
            {
                State = SIZE;
                return;
            }

            if(dy > 1)
            {
                lessthany = Renderer::angle_h;
            }
            else if(dy < 1)
            {
                morethany = Renderer::angle_h;
            }
            Renderer::angle_h = (morethany + lessthany) / 2;
        }
        first = false;
        lasty = y;
        STATE_ANGLE_H = ++STATE_ANGLE_H % 2;
    }


    void drawSIZE()
    {
        ofSetColor(0,0,255);
        ofCircle(0.2,0.2,0.01);
    }
    void TapSIZE(float x, float y)
    {
        float dx= -0.3/(x-0.5);
        float dy= -0.3/(y-0.5);
        if (abs(1.0f-dx) < MAX_SIZE_DISTORTION && abs(1.0f-dy) < MAX_SIZE_DISTORTION)
        {
            State=DONE;
            return;
        }
        Renderer::width_offset *= dx;
        Renderer::height_offset *= dy;
    }
};


class CalibratorObject: public OnTable< tuio::CanDirectObjects < Graphic > >
{
    unsigned int fid;
    Calibrator cal;
    tuio::DirectObject * obj;
    public:
    CalibratorObject(unsigned int f_id):fid(f_id),obj(NULL)
    {
        cal.Deactivate();
    }
    void newObject(tuio::DirectObject * object)
    {
        if(!obj and object->f_id == fid)
        {
            obj = object;
            cal.Activate();
        }
    }
    void removeObject(tuio::DirectObject * object)
    {
        if(obj == object)
        {
            cal.Deactivate();
            obj = NULL;
        }
    }
};

#endif // CALIBRATOR_HPP_INCLUDED
