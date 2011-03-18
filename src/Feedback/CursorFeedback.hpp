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

#ifndef CURSORFEEDBACK_H_INCLUDED
#define CURSORFEEDBACK_H_INCLUDED

#include "ofMain.h"
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
        int sid;
        HistoryPoint(int sid, float x, float y):
        MAX_SECONDS(ofxGlobalConfig::getRef("FEEDBACK:CURSOR:MAX_TAIL_SECONDS",0.5f))
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
            static int & R = ofxGlobalConfig::getRef("FEEDBACK:CURSOR:COLOR:R",255);
            static int & G = ofxGlobalConfig::getRef("FEEDBACK:CURSOR:COLOR:G",0);
            static int & B = ofxGlobalConfig::getRef("FEEDBACK:CURSOR:COLOR:B",0);
            ///Draws cursor
            ofSetColor(R,G,B);
            ofCircle(xpos,ypos,0.007);
            ///Draws trace
            ofSetLineWidth(3);
            float actual_time = ofGetElapsedTimef();
            ofEnableAlphaBlending();
            glDisable(GL_DEPTH_TEST);
            glBegin(GL_LINE_STRIP);
            for (std::list<time_point>::iterator it = points.begin(); it != points.end(); it++){
                ofSetColor(R,G,B,(int)(255-255*(actual_time-it->time)/MAX_SECONDS));
                glVertex2f(it->point.getX(),it->point.getY());
            }
            glEnd();
            glEnable(GL_DEPTH_TEST);
            ofDisableAlphaBlending();
        }
};

class CursorFeedback: public CanBasicFingers < NotificationGraphic > {

    private:
        std::map<int,HistoryPoint*> finger_map;

    public:
        CursorFeedback();
        //CursorFeedback(Area * a);
        ~CursorFeedback();
        virtual void addTuioCursor(int id, float xpos,float ypos,float xspeed,float yspeed,float maccel);
        virtual void updateTuioCursor(int id, float xpos,float ypos,float xspeed,float yspeed,float maccel);
        virtual void removeTuioCursor(int id);
    protected:
        void update();
        void draw();

};


#endif // CURSORFEEDBACK_H_INCLUDED
