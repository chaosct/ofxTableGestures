/*

    OF-TangibleFramework . Framework for Taller de Sistemes Interactius I
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

#ifndef CURSORFEEDBACK_H_INCLUDED
#define CURSORFEEDBACK_H_INCLUDED

#include "ofMain.h"
#include "tuioApp.hpp"
#include "InputGestureBasicFingers.hpp"
#include "Graphic.hpp"
#include "DirectPoint.hpp"
#include <map>
#include <list>

class time_point{
    public:
        time_point(float _time, DirectPoint p):time(_time),point(p){}
        float time;
        DirectPoint point;
};

class HistoryPoint: private DirectPoint{
    private:
        std::list<time_point> points;
        float & MAX_SECONDS;
    public:
        int32 sid;
        HistoryPoint(int32 sid, float x, float y):
        MAX_SECONDS(GlobalConfig::getRef("FEEDBACK:CURSOR:MAX_TAIL_SECONDS",0.5f))
        {
            SetPoint(x,y);
        }
        void SetPoint(float x, float y){
            xpos = x;
            ypos = y;
            points.push_back(time_point(ofGetElapsedTimef(),DirectPoint(*this)));
        }
        void Update(float time){
            while (points.size() != 0 && time-points.front().time > MAX_SECONDS )
                points.pop_front();
        }
        void Draw(){
            ///Draws cursor
            ofSetColor(255,0,0);
            ofCircle(xpos,ypos,0.007);
            ///Draws trace
            ofSetLineWidth(3);
            float actual_time = ofGetElapsedTimef();
            ofEnableAlphaBlending();
            glDisable(GL_DEPTH_TEST);
            glBegin(GL_LINE_STRIP);
            for (std::list<time_point>::iterator it = points.begin(); it != points.end(); it++){
                ofSetColor(255,0,0,255-255*(actual_time-it->time)/MAX_SECONDS);
                glVertex2f(it->point.getX(),it->point.getY());
            }
            glEnd();
            glEnable(GL_DEPTH_TEST);
            ofDisableAlphaBlending();
        }
};

class CursorFeedback: public tuio::CanBasicFingers < NotificationGraphic > {

    private:
        std::map<int32,HistoryPoint*> finger_map;

    public:
        CursorFeedback();
        CursorFeedback(Area * a);
        ~CursorFeedback();
        virtual void addTuioCursor(int32 id, float xpos,float ypos,float xspeed,float yspeed,float maccel);
        virtual void updateTuioCursor(int32 id, float xpos,float ypos,float xspeed,float yspeed,float maccel);
        virtual void removeTuioCursor(int32 id);
    protected:
        void update();
        void draw();

};


#endif // CURSORFEEDBACK_H_INCLUDED
