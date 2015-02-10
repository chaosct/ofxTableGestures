        /*

    ofxTableGestures (formerly OF-TangibleFramework)
    Developed for Taller de Sistemes Interactius I
    Universitat Pompeu Fabra

    Copyright (c) 2011 Daniel Gallardo Grassot <daniel.gallardo@upf.edu>

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

#ifndef POLYGON_H
#define POLYGON_H

#include "Graphic.hpp"
#include "ofImage.h"
#include "ofPolyline.h"

namespace tableGraphics {
    class Polygon : public Graphic{
        public:
            Polygon();
            Polygon(vector<ofPoint>&);

            void draw();
            void clear();
            bool collide(const ofPoint& point);

            void addVertex(const ofVec2f& vertex);

            void SetTexture(ofImage&);
            void SetTexture(const std::string& path);
            void setStrokeWidth(float width);
            void setStrokeColor(const ofColor &iColor);

            // Generate circle, and optionally a star
            //   with inner radius set in third parameter.
            void circle(float radius, int res = 64, float star = 0);

            // Generate rectangle. Use stroke for rounded corners.
            void rectangle(float width, float height);

            enum toDraw{ FILL, STROKE, ALL };
            void setDraw(toDraw selector, bool draw);

        private:
            bool processed;
            ofPolyline outline;
            ofPolyline stroke;
            ofVboMesh mesh;
            ofVboMesh strokeMesh;

            bool figureVisible;
            bool strokeVisible;
            bool has_texture;
            ofImage texture;
            ofColor strokeColor;
            float strokeWidth;

            bool stretchTexture;
            bool isEmpty;

            void mapTexture();
            void drawFill();
            void drawStroke();
            void buildFill();
            void buildStroke();
            inline float determinant(const ofVec2f& dir1, const ofVec2f& dir2);
        };
}

#endif // POLYGON_H

