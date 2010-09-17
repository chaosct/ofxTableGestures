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

#include "container.hpp"
#include "Shapes.hpp"

using namespace shapes;
namespace simulator
{
void object::Draw(){
    ofSetLineWidth(0.2f);
    ofPushMatrix();
    ofTranslate(xpos,ypos);
    ofRotateZ(angle*180/PI);
    //Stroke
    ofPushMatrix();
    ofScale(0.91f,0.91f,1.0f);
    if(!isUp){
        ofNoFill();
        ofSetColor(80,80,80,90);
        Figure_shape::Instance().drawShape(fid,false);
        ofFill();
    }
    ofEnableAlphaBlending();
    ofSetColor(100,100,200,90);
    //body
    Figure_shape::Instance().drawShape(fid,false);
    ofPopMatrix();
    ofSetColor(255,0,0);
    //rotation line
    ofPushMatrix();
    ofLine(0,0,0,OBJECT_RADIUS*ofGetHeight()/2);
    ofPopMatrix();
    ofDisableAlphaBlending();
    ofSetColor(0xFFFFFF);
    std::stringstream msg;
    msg << fid;
    //text
    ofDrawBitmapString(msg.str(), 0, 0);
    ofPopMatrix();
}
}
