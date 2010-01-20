#ifndef CURSORFEEDBACK_H_INCLUDED
#define CURSORFEEDBACK_H_INCLUDED

#include "ofMain.h"
#include "tuioApp.h"
#include "InputGestureClasses.h"
#include "InputListener.h"
using namespace tuio;

#include <map>
#include <list>

#define MAX_SECONDS 2.0f
class time_point{
    public:
        time_point(float _time, DirectPoint p):time(_time),point(p){}
        float time;
        DirectPoint point;
};

class HistoryPoint: private DirectPoint{
    private:
        std::list<time_point> points;
    public:
        int32 sid;
        HistoryPoint(int32 sid, float x, float y){
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
            ofCircle(xpos*ofGetWidth(),ypos*ofGetHeight(),10);
            ///Draws trace
            glBegin(GL_LINE_STRIP);
            for (std::list<time_point>::iterator it = points.begin(); it != points.end(); it++){
                glVertex2f(it->point.xpos*ofGetWidth(),it->point.ypos*ofGetHeight());
            }
            glEnd();
        }
};

class CursorFeedback: public CanBasicFingers < Listener > {
    private:
        std::map<int32,HistoryPoint*> finger_map;
    public:
        CursorFeedback();
        ~CursorFeedback();
        void Update();
        void Draw();
        virtual void addTuioCursor(int32 id, float xpos,float ypos,float xspeed,float yspeed,float maccel);
        virtual void updateTuioCursor(int32 id, float xpos,float ypos,float xspeed,float yspeed,float maccel);
        virtual void removeTuioCursor(int32 id);
};

#endif // CURSORFEEDBACK_H_INCLUDED
