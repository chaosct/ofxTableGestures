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

#ifndef DFIGURE_H
#define DFIGURE_H

#include "BoundingBox.h"
#include <string>
#include "ofMain.h"
#include "Matrix.h"

namespace Figures
{
    class Figure
    {
        public:
            Figure();
            virtual ~Figure();
            void SetTexture(const std::string & path);
            void SetTexture(ofImage& image);
            void Draw();
            void DrawStroke();
            bool Collide(ofPoint const & point);
            virtual void GetCentre(float & x, float & y);
            ofPoint GetCentre();
        protected:
            BoundingBox bbox;
            bool has_texture;
            ofImage texture;
            Matrix matrix;

            virtual void RebuildGeometry()=0;
            virtual void Design()=0;
            virtual void DesignStroke()=0;
            virtual bool CheckCollision(ofPoint const & point)=0;
    };
}
#endif // DFIGURE_H
