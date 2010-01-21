/*

    TSIframework . Framework for Taller de Sistemes Interactius I
    Universitat Pompeu Fabra

    Copyright (c) 2009 Daniel Gallardo Grassot <daniel.gallardo@upf.edu>

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
#include "Shapes.hpp"

#define CURSOR_RADIUS 0.01
#define OBJECT_RADIUS 0.07
class Figure_shape;

namespace simulator{
    class container{
        private:
            int xpos_old;
            int ypos_old;
        public:
            unsigned int sid;
            int xpos, ypos;
            float xspeed,yspeed,maccel;
            bool mouse_on;
        public:
            container(unsigned int _sid, int _xpos,int _ypos,float _xspeed,float _yspeed,float maccel):
                sid(_sid),xpos(_xpos),ypos(_ypos),xspeed(_xspeed),yspeed(_yspeed),mouse_on(false){
                    xpos_old = xpos;
                    ypos_old = ypos;
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
            virtual void Add(int x, int y){
                xpos_old = x;
                ypos_old = y;
            }
            virtual void Update(int x, int y){
                xpos += x-xpos_old;
                ypos += y-ypos_old;
                xpos_old=x;
                ypos_old=y;
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
            cursor(unsigned int _sid, int _xpos,int _ypos,float _xspeed,float _yspeed,float maccel):
                container(_sid,_xpos,_ypos,_xspeed,_yspeed,maccel),isHolded(false),isSelected(false){}
            void Draw(){
                ofPushMatrix();
                ofEnableAlphaBlending();
                if(isSelected)ofSetColor(50,150,50,100);
                else ofSetColor(100,100,100,100);
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
        public:
            unsigned int fid;
            float angle, rspeed,raccel;
            int tray_number;
            bool isUp;
        public:
            object(unsigned int _sid,unsigned int _fid, int _xpos,int _ypos,float _angle,float _xspeed,float _yspeed,float _rspeed,float _maccel,float _raccel,int _trayNumber=0):
                container(_sid,_xpos,_ypos,_xspeed,_yspeed,maccel),fid(_fid),angle(_angle),rspeed(_rspeed),raccel(_raccel),tray_number(_trayNumber),isUp(false){}
            void Draw();
            bool Collide(int x, int y){
                if(GetDistance(x,y)<= OBJECT_RADIUS*ofGetHeight()/2) return true;
                return false;
            }
    };
}

#endif
