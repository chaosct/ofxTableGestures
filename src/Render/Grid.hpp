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

#ifndef _GRID
#define _GRID

#include "Graphic.hpp"
#include "ofMesh.h"
#include "ofPath.h"

class Grid : public Graphic{
    public:
        Grid(int _w_lines = 6, int _h_lines = 6);
        void draw();
        void clear();
        void setMode(int calibration_mode);

    private:
        int mode;
        int w_lines;
        int h_lines;

        ofMesh scaleArrow;
        ofPath grid;
        ofPath rotateArrow;

        static const float lineWidth;
        static const float center;
        static const float baseSize;
        static const ofColor arrowsColor;
        static const ofVec2f scaleArrowVerts[9];

        void generateGrid();
        void arrows_translate();
        void arrows_rotate();
        void arrows_scale();
        void arrows_tilt();
        void drawRotateArrow();
};

#endif

