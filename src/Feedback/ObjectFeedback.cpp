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

#include "ObjectFeedback.hpp"
#include "GenericManager.hpp"
#include "GraphicDispatcher.hpp"
#include "Polygon.hpp"

const float ObjectFeedback::squareSize = 0.08f;

ObjectFeedback::ObjectFeedback() {
    loadGraphics();
    ofAddListener(InputGestureDirectObjects::newObject, this, &ObjectFeedback::newObject);
    ofAddListener(InputGestureDirectObjects::removeObject, this, &ObjectFeedback::removeObject);
}

ObjectFeedback::~ObjectFeedback() {
    ofRemoveListener(InputGestureDirectObjects::newObject, this, &ObjectFeedback::newObject);
    ofRemoveListener(InputGestureDirectObjects::removeObject, this, &ObjectFeedback::removeObject);
}

void ObjectFeedback::newObject(InputGestureDirectObjects::newObjectArgs& eventArgs){
    tableGraphics::Polygon* newGraphic;
    GenericManager::get<GraphicDispatcher>()->createGraphic(newGraphic);
    setGraphic(eventArgs.object->f_id, newGraphic);
    objectGraphic newObject = { eventArgs.object, newGraphic, false };
    graphics.push_back(newObject);
}

void ObjectFeedback::removeObject(InputGestureDirectObjects::removeObjectArgs& eventArgs){
    std::vector<objectGraphic>::iterator it = std::find(graphics.begin(), graphics.end(), eventArgs.object);
    if (it != graphics.end()){
        (*it).toDelete = true;
    }
}

void ObjectFeedback::update() {
    for (std::vector<objectGraphic>::iterator it = graphics.begin();
         it != graphics.end();
         it++){
        objectGraphic& obj = *it;
        ofMatrix4x4 matrix = obj.graphic->getMatrix();
        ofVec2f scale = matrix.getScale() * 0.75f;
        float angle = obj.object->orientation * 180/PI;
        matrix.setRotate(ofQuaternion(angle, ofVec3f(0, 0, 1)));
        matrix.setTranslation(obj.object->x, obj.object->y, 0);
        if (obj.toDelete){
            matrix.glScale(scale);
            if (scale.x < 0.001f && scale.y < 0.001f){
                GenericManager::get<GraphicDispatcher>()->removeGraphic(obj.graphic);
                graphics.erase(it);
                it--;
                continue;
            }
        }
        obj.graphic->setMatrix(matrix);
    }
}

void ObjectFeedback::setGraphic(int id, tableGraphics::Polygon* polygon){
    const float circleSize = squareSize * 0.625f;
    std::vector<colorShape>::iterator it = std::find(shapes.begin(), shapes.end(), id);
    if (it == shapes.end()){
        colorShape newShape;
        shapes.push_back(newShape);
        it = --shapes.end();
    }
    switch(it->shape){
    case SQUARE:
        polygon->rectangle(squareSize, squareSize);
        break;
    case SQUARE_ROUNDED:
        polygon->rectangle(squareSize * 0.85f, squareSize * 0.85f);
        polygon->setStrokeWidth(squareSize * 0.1f);
        polygon->setStrokeColor(it->color);
        polygon->setDraw(tableGraphics::Polygon::STROKE, 1);
        break;
    case CIRCLE:
        polygon->circle(circleSize);
    case PENTAGON:
        polygon->circle(circleSize, 5);
        break;
    case DODECAHEDRON:
        polygon->circle(circleSize, 12);
        break;
    case STAR:
        polygon->circle(circleSize, 12, circleSize * 0.9f);
        break;
    default:
        break;
    }
    polygon->setColor(it->color);
}

tableGraphics::Polygon* ObjectFeedback::getGraphic(int fid){
    std::vector<objectGraphic>::iterator it = std::find(graphics.begin(), graphics.end(), fid);
    if (it != graphics.end()){
        return it->graphic;
    }else{
        return NULL;
    }
}

unsigned int ObjectFeedback::getNumObjects(){
    unsigned int size = shapes.size();

    // Exclude default colorShape if it exists
    if (std::find(shapes.begin(), shapes.end(), -1) != shapes.end()){
        --size;
    }

    return size;
}

void ObjectFeedback::loadGraphics(){
    std::ifstream infile(ofToDataPath(NAMEPATH).c_str());
    if (infile.is_open()){
        char first;
        while (!infile.eof()){
            infile >> first;
            if (first == 'o'){
                int f_id;
                std::string shape;
                int r, g, b, a;
                infile >> f_id >> shape >> r >> g >> b >> a;

                colorShape newShape(f_id);
                if (!shape.compare("square")){
                    newShape.shape = SQUARE;
                }else if (!shape.compare("circle")){
                    newShape.shape = CIRCLE;
                }else if (!shape.compare("star")){
                    newShape.shape = STAR;
                }else if (!shape.compare("square_rounded")){
                    newShape.shape = SQUARE_ROUNDED;
                }else if (!shape.compare("pentagon")){
                    newShape.shape = PENTAGON;
                }else if (!shape.compare("dodecahedron")){
                    newShape.shape = DODECAHEDRON;
                }
                newShape.color = ofColor(r, g, b, a);
                shapes.push_back(newShape);
            }
            std::string tmp;
            getline(infile, tmp);
            first = 0;
        }
    }
}

