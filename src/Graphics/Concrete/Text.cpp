#include "Text.hpp"

using namespace tableGraphics;

Text::Text() : globalSize(ofxGlobalConfig::getRef("PROGRAM:TEXTSIZE", 1.0f)),
                usingGlobalSize(true){
    loadFont(11);
}

bool Text::collide(const ofPoint& point){
    return font.getStringBoundingBox(text.str(), 0, 0).inside(point);
}

void Text::loadFont(int size, string name){
    if (name == ""){
        name = "verdana.ttf";
    }

    // Arbitrary scaling, but consistent between the two modes.
    if (ignoresMatrixStack()){
        scaling = 1;
        font.loadFont(ofxGlobalConfig::getRef<std::string>("PROGRAM:HELPFONT", name), size);
    }else{
        scaling = size / 65536.0f;
        font.loadFont(ofxGlobalConfig::getRef<std::string>("PROGRAM:HELPFONT", name), 64);
    }
}

void Text::draw(){
    float scale;
    if (usingGlobalSize && !ignoresMatrixStack()){
        scale = scaling * globalSize;
    }else{
        scale = scaling;
    }
    ofScale(scale, scale);
    font.drawString(text.str(), 0, 0);
}

void Text::clear(){
    text.str("");
}

void Text::useGlobalSize(bool b){
    usingGlobalSize = b;
}

