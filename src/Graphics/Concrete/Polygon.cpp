/*

    ofxTableGestures (formerly OF-TangibleFramework)
    Developed for Taller de Sistemes Interactius I
    Universitat Pompeu Fabra

    Copyright (c) 2011 Daniel Gallardo Grassot <daniel.gallardo@upf.edu>

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

#include "Polygon.hpp"
#include "ofTessellator.h"

using namespace tableGraphics;

Polygon::Polygon() : processed(false), figureVisible(true), strokeVisible(false), has_texture(false), stretchTexture(false),
                     isEmpty(true){
    mesh.setMode(OF_PRIMITIVE_TRIANGLES);
}

Polygon::Polygon(vector<ofPoint>& points) : stretchTexture(false),
                                            isEmpty(false){
    mesh.setMode(OF_PRIMITIVE_TRIANGLES);

    if (points.size() == 0){
        isEmpty = true;
    }else{
        outline.addVertices(points);
    }
    canCollide = true;
}

void Polygon::SetTexture(const std::string & path) {
    if(texture.loadImage(path)) {
        mapTexture();
        has_texture = true;
    } else {
        has_texture = false;
    }
}

void Polygon::SetTexture(ofImage& tex) {
    if(tex.getHeight() && tex.getWidth()) {
        texture = tex;
        mapTexture();
        has_texture = true;
    } else {
        has_texture = false;
    }
}

void Polygon::setStrokeWidth(float width) {

    // Allow > 1.0f for retro-compatibility only
    //   (stroke width was expressed
    //   in terms of absolute pixels)

    if (width >= 1.0f) {
        width *= 0.001;
    } else if (width < 0) {
        width = 0;
    }
    strokeWidth = width;
    buildStroke();
}

void Polygon::setStrokeColor(const ofColor &iColor) {
    strokeColor = iColor;
}

void Polygon::setDraw(toDraw selector, bool state) {
    switch (selector) {
    case FILL:
        figureVisible = state;
        break;
    case STROKE:
        strokeVisible = state;
        if(strokeVisible){
            buildStroke();
        }
        break;
    case ALL:
        figureVisible = state;
        strokeVisible = state;
        break;
    default:
        break;
    }
}

void Polygon::draw() {
    if (isEmpty) {
        return;
    }
    if (!processed){
        buildFill();
        processed = true;
    }
    if (figureVisible) {
        drawFill();
    }
    if (strokeVisible) {
        drawStroke();
    }
}

void Polygon::addVertex(const ofVec2f& vertex){
    outline.addVertex(vertex);
    processed = false;
    isEmpty = false;
}

void Polygon::clear(){
    outline.clear();
    stroke.clear();
    mesh.clear();
    strokeMesh.clear();
}

void Polygon::circle(float radius, int res, float star){
    clear();
    if (res < 3){
        return;
    }
    if (star > 0){
        res *= 2;
    }
    float angleStep = 2*PI / res;
    int i = 0;
    ofVec2f vertex;
    const float offset = PI * 3/2;
    for (float angle = 0; angle < 2*PI; angle += angleStep){
        float angleOff = angle + offset;
        if (star > 0 && i++ % 2){
            vertex.set(star*cos(angleOff), star*sin(angleOff));
        }else{
            vertex.set(radius*cos(angleOff), radius*sin(angleOff));
        }
        addVertex(vertex);
    }
}

void Polygon::rectangle(float width, float height){
    clear();
    ofVec2f vertex;
    vertex.set(-width/2, -height/2);
    addVertex(vertex);
    vertex.set(width/2, -height/2);
    addVertex(vertex);
    vertex.set(width/2, height/2);
    addVertex(vertex);
    vertex.set(-width/2, height/2);
    addVertex(vertex);
}

bool Polygon::collide(const ofPoint& point){
    if (isEmpty){
        return false;
    }
    bool strokeCollide = false;
    if (stroke.isClosed()){
        strokeCollide = stroke.inside(point);
    }
    return outline.inside(point) || strokeCollide;
}

void Polygon::mapTexture(){
    texture.getTextureReference().setTextureWrap(GL_CLAMP_TO_BORDER, GL_CLAMP_TO_BORDER);
    ofRectangle boundBox = outline.getBoundingBox();
    ofVec2f min = boundBox.getMin();
    ofVec2f max = boundBox.getMax();
    ofVec2f center = boundBox.getCenter();
    float width = boundBox.getWidth();
    float height = boundBox.getHeight();
    vector<ofVec2f> texCoords;
    vector<ofVec3f> vertices = mesh.getVertices();
    for (vector<ofVec3f>::iterator vertex = vertices.begin(); vertex != vertices.end(); vertex++){
        if (!stretchTexture){
            if (width > height){
                min.x = center.x - height/2;
                max.x = center.x + height/2;
            }
            else if (height > width){
                min.y = center.y - width/2;
                max.y = center.y + width/2;
            }
        }
        ofVec2f coord = (*vertex - min) / (max - min);
        texCoords.push_back(coord);
    }
    mesh.clearTexCoords();
    mesh.addTexCoords(texCoords);
}

void Polygon::drawFill(){
    if (has_texture){
        mesh.enableTextures();
        texture.getTextureReference().bind();
        mesh.draw();
        texture.getTextureReference().unbind();
    }else{
        mesh.disableTextures();
        mesh.draw();
    }
}

void Polygon::drawStroke(){
    ofSetColor(strokeColor);
    strokeMesh.draw();
}

void Polygon::buildFill(){
    outline.close();
    mesh.clear();
    ofTessellator().tessellateToMesh(outline, OF_POLY_WINDING_POSITIVE, mesh, true);
    if (has_texture){
        mapTexture();
    }
}

void Polygon::buildStroke(){
    vector<ofVec3f> vertices = outline.getVertices();
    if (vertices.empty()){
	return;
    }
    vector<ofVec3f>::iterator vertexIt;

    // Check if outline's vertices go clock-wise or counter clock-wise
    int cw = 0;
    for (vertexIt = vertices.begin(); vertexIt != vertices.end(); vertexIt++){
        ofVec3f vertex = *vertexIt;
        ofVec3f previous = *(vertexIt - 1);
        ofVec3f next = *(vertexIt + 1);
        if (vertex == vertices.front()){
            previous = vertices.back();
        }
        if (vertex == vertices.back()){
            next = vertices.front();
        }
        ofVec2f direction1 = (vertex - previous).normalize();
        ofVec2f direction2 = (next - vertex).normalize();
        if (determinant(direction1, direction2) > 0){
            cw++;
        }else{
            cw--;
        }
    }
    bool isClockwise = (cw >= 0) ? true : false;

    stroke.clear();
    stroke.addVertices(outline.getVertices());
    stroke.addVertex(outline.getVertices().front());
    for (vertexIt = vertices.begin(); vertexIt != vertices.end(); vertexIt++){
        ofVec2f vertex = *vertexIt;
        ofVec2f previous = *(vertexIt - 1);
        ofVec2f next = *(vertexIt + 1);
        if (vertex == vertices.front()){
            previous = vertices.back();
        }
        if (vertex == vertices.back()){
            next = vertices.front();
        }
        ofVec3f direction1 = (vertex - previous).normalize();
        ofVec3f direction2 = (next - vertex).normalize();
        float det = determinant(direction1, direction2);
        if(det == 0){
            // Straight line, so go to next vertex.
            continue;
        }
        bool isConvex = (det < 0) ^ isClockwise;
        if (!isConvex){
            float angle2 = direction1.angleRad(direction2);
            angle2 = (angle2 - PI)/2;
            ofVec2f result2 = direction2.getRotatedRad(angle2, ofVec3f(0,0, isClockwise ? 1 : -1));
            float distance = -strokeWidth / sin(angle2);
            stroke.addVertex(vertex + result2 * distance);
        }else{
            ofVec3f rotAxis;
            if (isClockwise){
                rotAxis.set(0, 0, -1);
            }else{
                rotAxis.set(0, 0, 1);
            }
            ofVec2f result1 = direction1.getRotatedRad(PI/2, rotAxis);
            stroke.addVertex(vertex + result1 * strokeWidth);
            float arcBegin = atan2(result1.y, result1.x) * RAD_TO_DEG;
            result1 = direction2.getRotatedRad(PI/2, rotAxis);
            float arcEnd = atan2(result1.y, result1.x) * RAD_TO_DEG;
            stroke.arc(vertex, strokeWidth, strokeWidth, arcBegin, arcEnd, isClockwise);
            stroke.addVertex(vertex + result1 * strokeWidth);
        }
    }
    stroke.addVertex(stroke[outline.getVertices().size() + 1]); // -Really close- the polyline
    stroke.close();
    strokeMesh.clear();
    ofTessellator().tessellateToMesh(stroke, OF_POLY_WINDING_ODD, strokeMesh, true);
}

float Polygon::determinant(const ofVec2f& dir1, const ofVec2f& dir2){
    static const float epsilon = 1e-5;
    float result = dir1.x * dir2.y - dir1.y * dir2.x;
    if (abs(result) <= epsilon){
        return 0;
    }else{
        return result;
    }
}
