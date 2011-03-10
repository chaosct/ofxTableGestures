/*

    ofxTableGestures (formerly OF-TangibleFramework)
    Developed for Taller de Sistemes Interactius I
    Universitat Pompeu Fabra

    Copyright (c) 2010 Daniel Gallardo Grassot <daniel.gallardo@upf.edu>

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

#ifndef _CONTAINER
#define _CONTAINER

#include "ofMain.h"

#define CURSOR_RADIUS 0.01
#define OBJECT_RADIUS 0.07

#define M_2PI M_PI*2

namespace simulator{
    class container{
        protected:
            float previous_time;
            float dt;

        private:
            int x_old;
            int y_old;

            int xpos_old, ypos_old;
            float mspeed_old;
            float mspeed;
        public:
            unsigned int sid;
            int xpos, ypos;
            float xspeed,yspeed,maccel;
            bool mouse_on;
        public:
            container(unsigned int _sid, int _xpos,int _ypos,float _xspeed,float _yspeed,float _maccel):
                sid(_sid),
                xpos(_xpos),
                ypos(_ypos),
                xspeed(_xspeed),
                yspeed(_yspeed),
                maccel(_maccel),
                mouse_on(false)
                {
                    x_old = xpos;
                    y_old = ypos;
                    xpos_old = xpos;
                    ypos_old = ypos;
                    previous_time = ofGetElapsedTimef();
                }
            ~container(){}
            float GetDistance(const container& cont){
                return distance(xpos,ypos,cont.xpos,cont.ypos);
            }
            float GetDistance(int x, int y){
                return distance(xpos,ypos,x,y);
            }
            virtual void Draw()=0;
            virtual bool Collide(int x, int y)=0;
            virtual void Add(int x, int y,bool only = false){
                x_old = x;
                y_old = y;
                previous_time = ofGetElapsedTimef();
                mspeed_old = 0;
            }

            virtual void Update(int x, int y,bool only = false){
                float actual_time = ofGetElapsedTimef();
                dt = previous_time - actual_time;
                previous_time = actual_time;
                xpos_old = xpos;
                ypos_old = ypos;
                xpos += x-x_old;
                ypos += y-y_old;
                x_old=x;
                y_old=y;
                if(dt == 0 )return;
                float dx = (float)(xpos - xpos_old)/ofGetScreenWidth();
                float dy = (float)(ypos - ypos_old)/ofGetScreenHeight();
                float dist = sqrt(dx*dx + dy*dy);

                mspeed_old = mspeed;
                mspeed = dist/dt;

                xspeed = dx/dt;
                yspeed = dy/dt;
                maccel = ( mspeed - mspeed_old) /dt;
            }

        protected:

            float distance (int x, int y, int a, int b)
            {
                float dx = x-a;
                float dy = y-b;
                return sqrtf(dx*dx+dy*dy);
            }

            float distance (float x, float y, float a, float b)
            {
                float dx = x-a;
                float dy = y-b;
                return sqrtf(dx*dx+dy*dy);
            }
    };

    class cursor:public container{
        public:
            bool isHolded;
            bool isSelected;
        public:
            cursor(unsigned int _sid, int _xpos,int _ypos,float _xspeed,float _yspeed,float _maccel):
                container(_sid,_xpos,_ypos,_xspeed,_yspeed,_maccel),isHolded(false),isSelected(false){}
            void Draw(){
                ofPushMatrix();
                ofEnableAlphaBlending();
                if(isSelected)ofSetColor(50,150,50,80);
                else ofSetColor(100,100,100,80);
                ofTranslate(xpos,ypos);
                //bug when windows is not a screen rectangle
                ofCircle(0,0,CURSOR_RADIUS*ofGetHeight());
                ofDisableAlphaBlending();
                ofPopMatrix();
            }
            bool Collide(int x, int y){
                if(GetDistance(x,y)<= CURSOR_RADIUS*ofGetHeight()) return true;
                return false;
            }
    };

    class object:public container{
        private:
            float angle_old;
            float previous_angle_time;
            float rspeed_old;
        public:
            float angle;
            unsigned int fid;
            float rspeed,raccel;
            int tray_number;
            bool isUp;
        public:
            object(unsigned int _sid,unsigned int _fid, int _xpos,int _ypos,float _angle,float _xspeed,float _yspeed,float _rspeed,float _maccel,float _raccel,int _trayNumber=0):
                container(_sid,_xpos,_ypos,_xspeed,_yspeed,_maccel),
                angle(_angle),
                fid(_fid),
                rspeed(_rspeed),
                raccel(_raccel),
                tray_number(_trayNumber),
                isUp(false){}
            void Draw();
            bool Collide(int x, int y){
                if(GetDistance(x,y)<= OBJECT_RADIUS*ofGetHeight()/2) return true;
                return false;
            }

            virtual void AddAngle(bool only = false){
                angle_old = angle;
                previous_angle_time = ofGetElapsedTimef();
                rspeed_old = 0;
                if(!only)
                    this->Add(0,0,true);
            }

            virtual void UpdateAngle(float _angle, bool only = false){
                float new_angle = ofGetElapsedTimef();
                float dta = previous_angle_time - new_angle;
                if(dta == 0) return;
                angle_old = angle;
                angle += _angle;
                if(angle >= M_2PI)angle = angle-M_2PI;
                if(angle < 0)angle = angle+M_2PI;

                float da = angle-angle_old;
                if (da>(M_PI*1.5f)) da-=M_2PI;
                else if (da<(M_PI*-1.5f)) da+=M_2PI;

                da = da/M_2PI;
                rspeed_old = rspeed;
                rspeed = da /dta;
                raccel = (rspeed - rspeed_old)/dta;
                if(!only)
                    this->Update(0,0,true);
            }

            virtual void Add(int x, int y,bool only = false){
                container::Add(x,y,only);
                if(!only)AddAngle(true);
            }

            virtual void Update(int x, int y,bool only = false){
                container::Update(x,y,only);
                if(!only)UpdateAngle(0,true);
            }
    };
}

#endif
