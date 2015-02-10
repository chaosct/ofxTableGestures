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
#include "ofGraphics.h" // Matrices operations
#include "ofAppRunner.h" // ofGetWindowSize()
#include <algorithm> // std::find()
#include "Graphic.hpp"

void GraphicDispatcher::Draw(){
    ofPoint winSize = ofGetWindowSize();

    for(GraphicsList::iterator it = graphics.begin(); it != graphics.end(); it++){
        if((*it).graphic->ignoresMatrixStack()){
            ofSetMatrixMode(OF_MATRIX_PROJECTION);
            ofPushMatrix();
            ofSetMatrixMode(OF_MATRIX_MODELVIEW);
            ofPushMatrix();

            ofSetupScreenOrtho(winSize.x, winSize.y);
            (*it).graphic->drawGraphic();

            ofSetMatrixMode(OF_MATRIX_PROJECTION);
            ofPopMatrix();
            ofSetMatrixMode(OF_MATRIX_MODELVIEW);
            ofPopMatrix();
        }else{
            (*it).graphic->drawGraphic();
        }
    }
}

Graphic* GraphicDispatcher::removeGraphic(Graphic* graphic){
    GraphicsList::iterator it = std::find(graphics.begin(), graphics.end(), graphic);
    if(it == graphics.end()){
        ofLogError("removeGraphic") << "Graphic not found!";
        return graphic;
    }
    graphic->clear();
    delete graphic;
    graphics.erase(it);
    graphics.sort();
    return NULL;
}

void GraphicDispatcher::setLayer(int newLayer, Graphic* graphic){
    GraphicsList::iterator it = std::find(graphics.begin(), graphics.end(), graphic);
    (*it).layer = std::make_pair(newLayer, ofGetElapsedTimef());
    graphics.sort();
}

void GraphicDispatcher::bringTop(Graphic* graphic){
    GraphicsList::iterator it = std::find(graphics.begin(), graphics.end(), graphic);
    (*it).layer.second = ofGetElapsedTimef();
    graphics.sort();
}

Graphic* GraphicDispatcher::Collide(const ofPoint & point){
    GraphicsList::reverse_iterator it;
    for (it = graphics.rbegin(); it != graphics.rend(); it++){
        if ((*it).graphic->collideGraphic(point)){
            return (*it).graphic;
        }
    }
    return NULL;
}
