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

#ifndef _GRAPHIC_HPP_
#define _GRAPHIC_HPP_

#include "ofGraphics.h"
#include "EventClient.hpp"
#include "ofShader.h"

class Graphic : public EventClient{
    public:
        Graphic();
        virtual ~Graphic() {}
        virtual void draw() = 0;
        virtual bool collide(const ofPoint&) { return false; }
        virtual void clear() = 0;

        void drawGraphic();
        bool collideGraphic(ofPoint const & point);

        void setColor(const ofColor& iColor);
        ofColor& getColor();

        void setPosition(const ofVec2f&, float angle = 0); // Angle is in degrees
        void setMatrix(ofMatrix4x4&);
        const ofMatrix4x4& getMatrix();
        void ignoreMatrixStack(bool);
        bool ignoresMatrixStack();

        // Passing an empty string as filePath unloads shaders
        bool loadShader(const string& filePath,
                        const string& defaultVertex = std::string(),
                        const string& defaultFragment = std::string());

        void setCollide(bool);
        void setVisible(bool);

    protected:
        bool visible;
        bool canCollide;
        ofShader shader;
 
    private:
        ofColor color;
        ofMatrix4x4 transformMatrix;
        bool bypassMatrix;
};

#endif //_GRAPHIC_HPP_
