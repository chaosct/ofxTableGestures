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

#include <fstream>
#include "Renderer_plane.hpp"
#include "ofMain.h"

void Renderer_plane::StartDistortion(){
    ofPushMatrix();
    ofTranslate(center_x,center_y,0);
    ofTranslate((ofGetWidth())/2,(ofGetHeight())/2,0);
    ofRotate(angle,0,0,1);
    ofRotate(angle_h,1,0,0);
    ofRotate(angle_w,0,1,0);
    ofScale(width_offset,height_offset,1);
    ofTranslate(-(ofGetWidth())/2,-(ofGetHeight())/2,0);
    Renderer::matrix = ofGetCurrentMatrix(OF_MATRIX_MODELVIEW);
}

void Renderer_plane::EndDistortion(){
    ofPopMatrix();
}
