/*

    ofxTableGestures (formerly OF-TangibleFramework)
    Developed for Taller de Sistemes Interactius I
    Universitat Pompeu Fabra

    Copyright (c) 2011 Carles F. Julià <carles.fernandez@upf.edu>

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

#ifndef FIGUREGRAPHIC_HPP_INCLUDED
#define FIGUREGRAPHIC_HPP_INCLUDED

#include "ofVectorMath.h"
#include "Graphic.hpp"
#include "Figure.h"

inline void ofMultMatrix(ofMatrix4x4 &m) {
    float a[] = {m(0,0),m(0,1),m(0,2),m(0,3),
                 m(1,0),m(1,1),m(1,2),m(1,3),
                 m(2,0),m(2,1),m(2,2),m(2,3),
                 m(3,0),m(3,1),m(3,2),m(3,3)};
    glMultMatrixf(a);
}

class FigureGraphic: public Graphic
{
    Figures::Figure * figure;
    bool testCollide;
    bool hasalpha;
    bool fill;
    bool hidden;
    public:
    ofColor color;
    ofMatrix4x4 transformation;
    FigureGraphic(Figures::Figure * f, int layer=APP_LAYER):Graphic(layer),figure(f),testCollide(true),hasalpha(false),fill(true),hidden(false){}
    ~FigureGraphic(){}
    inline bool Collide(ofPoint const & point)
    {
        return testCollide && figure->Collide(point);
    }
    void draw()
    {
        if(hidden)
        {
            ofPushMatrix();
            ofMultMatrix(transformation);
            glGetDoublev(GL_MODELVIEW_MATRIX,figure->getMatrix().data);
            ofPopMatrix();
        }
        else
        {
            ofPushStyle();
            ofPushMatrix();
            ofMultMatrix(transformation);
            if(hasalpha)
            {
                ofEnableAlphaBlending();
                ofSetColor(color.r,color.g,color.b,color.a);
            }
            else
            {
                ofSetColor(color.r,color.g,color.b);
            }
            if(fill)
            {figure->Draw();}
            else
            {figure->DrawStroke();}
            if(hasalpha)
            {
                ofDisableAlphaBlending();
            }
            ofPopMatrix();
            ofPopStyle();
        }
    }
    void canCollide(bool can){testCollide = can;}
    bool canCollide(){return testCollide;}
    void hasAlpha(bool has){hasalpha = has;}
    bool hasAlpha(){return hasalpha;}
    bool getFill(){return fill;}
    void setFill(bool Fill){fill = Fill;}
    Figures::Figure * getFigure(){return figure;}
    void setFigure(Figures::Figure * f){figure = f;}
    bool isHidden() {return hidden;}
    void isHidden(bool is){hidden = is;}
};


#endif // FIGUREGRAPHIC_HPP_INCLUDED
