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

#include "GraphicDispatcher.hpp"

Graphic::Graphic():layer(APP_LAYER){
    GraphicDispatcher::Instance().AddGraphic(this);
}

Graphic::Graphic(int _layer):layer(_layer){
    GraphicDispatcher::Instance().AddGraphic(this);
}

///Copy constructor: this allows to copy graphic-herited members of classes
Graphic::Graphic(Graphic & original):layer(original.layer)
{
    GraphicDispatcher::Instance().AddGraphic(this);
}

int Graphic::GetLayer(){
    return layer;
}

Graphic::~Graphic(){
    GraphicDispatcher::Instance().RemoveGraphic(this);
}

void Graphic::BringTop(){
    GraphicDispatcher::Instance().bring_top(this);
}

bool Graphic::Collide(ofPoint const & point)
{
    return false;
}

void Graphic::Position(float & x, float & y)
{
    x = -1;
    y = -1;
}

void Graphic::SafeDelete()
{
    GraphicDispatcher::I().SafeDeleteGraphic(this);
}
