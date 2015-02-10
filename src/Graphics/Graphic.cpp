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

#include "Graphic.hpp"
#include "ofFileUtils.h" // ofFile in loadShader()

Graphic::Graphic() : visible(true), canCollide(false), bypassMatrix(false){}

void Graphic::setColor(const ofColor& iColor){
    color = iColor;
}

ofColor& Graphic::getColor(){
    return color;
}

void Graphic::drawGraphic(){
    if(!visible){
        return;
    }
    ofPushMatrix();
    ofMultMatrix(transformMatrix);
    ofPushStyle();
    ofEnableAlphaBlending();
    ofSetColor(color);
    if(shader.isLoaded()){
        shader.begin();
        draw();
        shader.end();
    }else{
        draw();
    }
    ofPopStyle();
    ofPopMatrix();
}

bool Graphic::collideGraphic(const ofPoint & point){
    if(canCollide){
        ofPoint localPoint = transformMatrix.getInverse().preMult(point);
        return collide(localPoint);
    }else{
        return false;
    }
}

void Graphic::setPosition(const ofVec2f& pos, float angle){
    transformMatrix.setTranslation(pos);
    transformMatrix.setRotate(ofQuaternion(angle, ofVec3f(0, 0, 1)));
}

void Graphic::setMatrix(ofMatrix4x4& m){
    transformMatrix = m;
}

const ofMatrix4x4& Graphic::getMatrix(){
    return transformMatrix;
}

void Graphic::ignoreMatrixStack(bool t){
    bypassMatrix = t;
}

bool Graphic::ignoresMatrixStack(){
    return bypassMatrix;
}

bool Graphic::loadShader(const string& filePath,
                        const string& defaultVert,
                        const string& defaultFrag){
    if (filePath.empty()){
        shader.unload();
        return true;
    }
    ofFile shaderFile;

    // Vertex shader
    shaderFile.open(filePath + ".vert", ofFile::ReadWrite);
    if (!shaderFile.exists()){
        shaderFile.create();
        shaderFile.open(filePath + ".vert", ofFile::ReadWrite);
    }
    if (!shaderFile.getSize()){
        if (defaultVert.empty()){
            return false;
        }
        ofLogNotice("Graphic::loadShader()") << "Writing default shader to " << filePath << ".vert";
        ofBuffer text("/* Default generated vertex shader */\n\n");
        text.append(defaultVert);
        text.append("\n\n/************************************/\n\n");
        shaderFile.writeFromBuffer(text);
    }
    shaderFile.close();

    // Fragment shader
    shaderFile.open(filePath + ".frag", ofFile::ReadWrite);
    if (!shaderFile.exists()){
        shaderFile.create();
        shaderFile.open(filePath + ".frag", ofFile::ReadWrite);
    }
    if (!shaderFile.getSize()){
        if (defaultFrag.empty()){
            return false;
        }
        ofLogNotice("Graphic::loadShader()") << "Writing default shader to " << filePath << ".frag";
        ofBuffer text("/* Default generated fragment shader */\n\n");
        text.append(defaultFrag);
        text.append("\n\n/************************************/\n\n");
        shaderFile.writeFromBuffer(text);
    }
    shaderFile.close();

    return shader.load(filePath);
}

void Graphic::setCollide(bool collide){
    canCollide = collide;
}

void Graphic::setVisible(bool v){
    visible = v;
}
