/*

    ofxTableGestures (formerly OF-TangibleFramework)
    Developed for Taller de Sistemes Interactius I
    Universitat Pompeu Fabra

    Copyright (c) 2010 Daniel Gallardo Grassot <daniel.gallardo@upf.edu>
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

#ifndef CURSORFEEDBACK_H_INCLUDED
#define CURSORFEEDBACK_H_INCLUDED

#include "ofMain.h"
#include "InputGestureBasicFingers.hpp"
#include "Graphic.hpp"
#include "DirectPoint.hpp"
#include <map>


class HistoryPoint : private DirectPoint{
    private:

        float & MAX_SECONDS;
        int MAX_POINTS;
        GLfloat * xycoordinates;
        GLubyte * colorcoordinates;
        float * times;

        int begin;
        int npoints;

    public:
        int sid;
        HistoryPoint(int sid, float x, float y):
        MAX_SECONDS(ofxGlobalConfig::getRef("FEEDBACK:CURSOR:MAX_TAIL_SECONDS",0.5f)),
        MAX_POINTS(ofxGlobalConfig::getRef("FEEDBACK:CURSOR:MAX_TAIL_POINTS",100)),
        begin(0),
        npoints(0)
        {
            xycoordinates = new GLfloat[(MAX_POINTS+1)*2];
            colorcoordinates = new GLubyte[(MAX_POINTS+1)*4];
            times = new float[MAX_POINTS];
            SetPoint(x,y);
        }
        ~HistoryPoint()
        {
            delete [] xycoordinates;
            delete [] colorcoordinates;
            delete [] times;
        }
        void SetPoint(float x, float y){
            xpos = x;
            ypos = y;

            if(npoints == MAX_POINTS)
            {
                begin= (begin+1)%MAX_POINTS;
                npoints--;
            }
            int pos = (begin + npoints) % MAX_POINTS;
            xycoordinates[pos*2] = x;
            xycoordinates[pos*2+1] = y;
            times[pos] = ofGetElapsedTimef();
            npoints++;

        }
        void Update(float time){

            while((npoints > 0 ) && (time-times[begin] > MAX_SECONDS) )
            {
                begin= (begin+1)%MAX_POINTS;
                npoints--;
            }
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

            unsigned int j = 0;
            for(int i = 0; i < MAX_POINTS; ++i)
            {
                colorcoordinates[j++] = R;
                colorcoordinates[j++] = G;
                colorcoordinates[j++] = B;
                colorcoordinates[j++] = (GLubyte) max(0.0f,255-255*(actual_time-times[i])/MAX_SECONDS);
            }

            colorcoordinates[j++] = colorcoordinates[0];
            colorcoordinates[j++] = colorcoordinates[1];
            colorcoordinates[j++] = colorcoordinates[2];
            colorcoordinates[j++] = colorcoordinates[3];

            xycoordinates[MAX_POINTS*2] = xycoordinates[0];
            xycoordinates[MAX_POINTS*2+1] = xycoordinates[1];

            ofEnableAlphaBlending();
            glDisable(GL_DEPTH_TEST);
            glEnableClientState(GL_VERTEX_ARRAY);
            glEnableClientState(GL_COLOR_ARRAY);
			glVertexPointer(2, GL_FLOAT, 0, xycoordinates);
			glColorPointer(4,GL_UNSIGNED_BYTE,0,colorcoordinates);
			glDrawArrays(GL_LINE_STRIP, begin, min(npoints,MAX_POINTS-begin+1));
			if(begin+npoints > MAX_POINTS)
			{
			    glDrawArrays(GL_LINE_STRIP, 0, (begin+npoints)%MAX_POINTS);
			}

			glDisableClientState(GL_COLOR_ARRAY);
			glDisableClientState(GL_VERTEX_ARRAY);
            glEnable(GL_DEPTH_TEST);
            ofDisableAlphaBlending();


        }
};

class CursorFeedback: public  NotificationGraphic {

    private:
        std::map<int,HistoryPoint*> finger_map;

    public:
        CursorFeedback();
        //CursorFeedback(Area * a);
        ~CursorFeedback();
        virtual void addTuioCursor(InputGestureBasicFingers::addTuioCursorArgs & a);
        virtual void updateTuioCursor(InputGestureBasicFingers::updateTuioCursorArgs & a);
        virtual void removeTuioCursor(InputGestureBasicFingers::removeTuioCursorArgs & a);
    protected:
        void update();
        void draw();

};


#endif // CURSORFEEDBACK_H_INCLUDED
