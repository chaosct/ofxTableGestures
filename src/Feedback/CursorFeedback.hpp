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

#include "InputGestureBasicFingers.hpp"
#include "autoGraphic.hpp"
#include "ofMesh.h"
#include "ofFbo.h"

class HistoryPoint {
    public:
        HistoryPoint(float _x, float _y) : currentPos(_x,_y), lastPos(currentPos) {}

        void SetPoint(float x, float y) {
            currentPos = ofPoint(x, y);
        }

        void Draw() {
            ofVec2f direction = currentPos - lastPos;

            // Draw trace
            if (direction != ofVec2f(0, 0)) {
                direction = direction.perpendicular();
                ofMesh mesh;
                mesh.setMode(OF_PRIMITIVE_TRIANGLE_STRIP);
                mesh.addVertex(lastPos + (pointWidth * direction));
                mesh.addVertex(lastPos + (-pointWidth * direction));
                mesh.addVertex(currentPos + (-pointWidth * direction));
                mesh.addVertex(currentPos + (pointWidth * direction));
                mesh.addTriangle(0, 1, 2);
                mesh.addTriangle(2, 3, 0);
                mesh.draw();
            }
            // Draw cursor
            ofCircle(currentPos.x, currentPos.y, pointWidth);
            lastPos = currentPos;
        }

    private:
        const static unsigned char pointWidth;
        ofPoint currentPos;
        ofPoint lastPos;
};

class CursorFeedback : public FeedbackGraphic {
    public:
        CursorFeedback();
        virtual ~CursorFeedback() {}
        virtual void addTuioCursor(InputGestureBasicFingers::addTuioCursorArgs & a);
        virtual void updateTuioCursor(InputGestureBasicFingers::updateTuioCursorArgs & a);
        virtual void removeTuioCursor(InputGestureBasicFingers::removeTuioCursorArgs & a);

    protected:
        virtual void draw();
        virtual void clear();

    private:
        std::map<int,HistoryPoint*> finger_map;
        const static unsigned short fboSize;
        ofFbo frame;
        ofFbo frameLast;
        ofPlanePrimitive drawPlane;
};


#endif // CURSORFEEDBACK_H_INCLUDED
