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

#include "CursorFeedback.hpp"

const unsigned char HistoryPoint::pointWidth = 4;
const unsigned short CursorFeedback::fboSize = 1024;

// Default shaders //////
static const string vertShader = "\
    #version 110 \n\
    varying vec2 texcoord; \n\
    void main(){ \n\
	texcoord = gl_MultiTexCoord0.st; \n\
        gl_Position = gl_ModelViewProjectionMatrix * gl_Vertex; \n\
    }";

static const string fragShader = "\
    #version 110 \n\
    uniform sampler2D tex; \n\
    varying vec2 texcoord; \n\
    void main(){ \n\
	float step = 1.0 / 1024.0; // From CursorFeedback::fboSize \n\
        gl_FragColor =  0.996 * texture2D(tex, texcoord); \n\
        gl_FragColor += 0.001 * texture2D(tex, texcoord + vec2(-step, 0));\n\
        gl_FragColor += 0.001 * texture2D(tex, texcoord + vec2(0, -step));\n\
        gl_FragColor += 0.001 * texture2D(tex, texcoord + vec2(step, 0));\n\
        gl_FragColor += 0.001 * texture2D(tex, texcoord + vec2(0, step));\n\
    }";
///////////////////////


CursorFeedback::CursorFeedback(){
    registerEvent(InputGestureBasicFingers::addTuioCursor,&CursorFeedback::addTuioCursor);
    registerEvent(InputGestureBasicFingers::updateTuioCursor,&CursorFeedback::updateTuioCursor);
    registerEvent(InputGestureBasicFingers::removeTuioCursor,&CursorFeedback::removeTuioCursor);

    ofDisableArbTex();
    frameLast.allocate(fboSize, fboSize, GL_RGBA);
    frame.allocate(fboSize, fboSize, GL_RGBA);
    frameLast.begin();
    ofClear(0,0,0,0);
    frameLast.end();

    const string& shaderPath = ofxGlobalConfig::getRef("FEEDBACK:CURSOR:SHADER", string("shaders/cursor"));
    loadShader(shaderPath, vertShader, fragShader);
    drawPlane.set(fboSize, fboSize, 2, 2);
}

void CursorFeedback::draw(){
    static int & R = ofxGlobalConfig::getRef("FEEDBACK:CURSOR:COLOR:R",255);
    static int & G = ofxGlobalConfig::getRef("FEEDBACK:CURSOR:COLOR:G",0);
    static int & B = ofxGlobalConfig::getRef("FEEDBACK:CURSOR:COLOR:B",0);

    ofPushStyle();
    ofEnableAlphaBlending();
    ofTexture texture(frame.getTextureReference());
    frame.begin();
        ofClear(255, 255, 255, 0);
        ofSetColor(255, 255, 255, 255);
        frameLast.draw(0, 0, fboSize, fboSize);
        ofSetColor(R, G, B, 255);
        for (std::map<int,HistoryPoint*>::iterator it = finger_map.begin(); it != finger_map.end(); it++) {
           it->second->Draw();
        }
    frame.end();
    texture = frame.getTextureReference();
    frameLast.begin();
        ofClear(0, 0, 0, 0);
        shader.begin();
        texture.bind();
        ofPushMatrix();
        ofTranslate(fboSize/2, fboSize/2);
        drawPlane.draw();
        ofPopMatrix();
        texture.unbind();
        shader.end();
    frameLast.end();
    frameLast.draw(0, 0, 1, 1);

    ofDisableAlphaBlending();
    ofPopStyle();
}

void CursorFeedback::clear(){
    finger_map.clear();
}

void CursorFeedback::addTuioCursor(InputGestureBasicFingers::addTuioCursorArgs & a){
    finger_map[a.id] = new HistoryPoint((a.xpos * fboSize), (a.ypos * fboSize));
}

void CursorFeedback::updateTuioCursor(InputGestureBasicFingers::updateTuioCursorArgs & a){
    finger_map[a.id]->SetPoint((a.xpos * fboSize), (a.ypos * fboSize));
}

void CursorFeedback::removeTuioCursor(InputGestureBasicFingers::removeTuioCursorArgs & a){
    HistoryPoint*tmp = finger_map[a.id];
    finger_map.erase(a.id);
    delete tmp;
}
