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

#include "ofMain.h"
#include "GraphicDispatcher.hpp"
#include <algorithm>
#include <functional>
#include <tr1/functional>
#include <cassert>

GraphicDispatcher::GraphicDispatcher():ngraphics(0) {
}

GraphicDispatcher::~GraphicDispatcher(){
}

void GraphicDispatcher::Draw(){
    std::for_each(graphics.begin(),graphics.end(),std::mem_fun(&Graphic::draw));
}

void GraphicDispatcher::Update(){
    GraphicsList l (graphics);
    std::for_each(l.begin(),l.end(),std::mem_fun(&Graphic::update));
}

void GraphicDispatcher::Resize(int w, int h){
    std::for_each(graphics.begin(),graphics.end(),
                  std::tr1::bind(&Graphic::resize,std::tr1::placeholders::_1,w,h));
}

void GraphicDispatcher::AddGraphic(Graphic* graphic){
    graphic->created_time = ngraphics++;
    graphics.insert(graphic);
}

void GraphicDispatcher::RemoveGraphic(Graphic* graphic){
    graphics.erase(graphic);
}

void GraphicDispatcher::bring_top(Graphic* graphic){
    graphics.erase(graphic);
    graphic->created_time = ngraphics++;
    graphics.insert(graphic);
}

Graphic * GraphicDispatcher::Collide(ofPoint const & point)
{
    GraphicsList::reverse_iterator it = std::find_if(graphics.rbegin(),graphics.rend(),
                                          std::tr1::bind(&Graphic::Collide,std::tr1::placeholders::_1,point));
    if (it != graphics.rend())
        return *it;
    return NULL;
}
