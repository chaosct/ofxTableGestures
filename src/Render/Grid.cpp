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

#include "Grid.hpp"

// Grid related constants
const float Grid::lineWidth = 0.004f;
const float Grid::center = 0.5f;
//const float Grid::center = lineWidth * 0.5f + 0.5f;

// Arrow related constants
const float Grid::baseSize = 0.1f;
const ofColor Grid::arrowsColor(255, 0, 0, 230);

const ofVec2f Grid::scaleArrowVerts[9] = { \
                    ofVec2f(-baseSize, -baseSize/8), \
                    ofVec2f(-baseSize, baseSize/8),  \
                    ofVec2f(0, baseSize/4),    \
                    ofVec2f(-baseSize, -baseSize/8), \
                    ofVec2f(0, baseSize/4),    \
                    ofVec2f(0, -baseSize/4),    \
                    ofVec2f(0, -baseSize/2),   \
                    ofVec2f(0, baseSize/2),    \
                    ofVec2f(baseSize, 0)       \
};

Grid::Grid(int _w_lines, int _h_lines) :
    mode(0),
    w_lines(_w_lines),
    h_lines(_h_lines),
    scaleArrow(OF_PRIMITIVE_TRIANGLES, \
        std::vector<ofVec3f>(scaleArrowVerts, scaleArrowVerts + \
            sizeof scaleArrowVerts / sizeof scaleArrowVerts[0]))
{
    rotateArrow.setPolyWindingMode(OF_POLY_WINDING_POSITIVE);
    rotateArrow.setCircleResolution(64);
    rotateArrow.setColor(arrowsColor);
    rotateArrow.arc(0, 0, baseSize, baseSize, 30, 350);
    rotateArrow.arcNegative(0, 0, baseSize - baseSize/5, baseSize - baseSize/5, 350, 30);
    rotateArrow.close();
    generateGrid();
}

void Grid::clear()
{
    setVisible(false);
}

void Grid::draw()
{
    grid.draw();
    ofPushStyle();
    ofEnableAlphaBlending();
    ofSetColor(arrowsColor);
    switch(mode)
    {
        case 0:
            arrows_translate();
            break;
        case 1:
            arrows_scale();
            break;
        case 2:
            arrows_rotate();
            break;
        case 3:
            arrows_tilt();
            break;
        default:
            break;
    }
    ofPopStyle();
}

void Grid::setMode(int m)
{
    mode = m;
}

void Grid::generateGrid()
{
    grid.setPolyWindingMode(OF_POLY_WINDING_POSITIVE);
    grid.setCircleResolution(64);

    //################################
    // Render the Main Grid
    //################################
    ///Draws the line-grid on a [0, 1] squared range.

    // Vertical lines
    for (int i = 0; i <= w_lines; i++)
    {
        grid.rectangle(i*(1.0f/w_lines) - lineWidth/2, 0, lineWidth, 1.0f);
    }
    // Horizontal lines
    for (int i = 0; i <= h_lines; i++)
    {
        grid.rectangle(0, i*(1.0f/h_lines) - lineWidth/2, 1.0f, lineWidth);
    }
    // Helping circles
    for (int i =0; i<=w_lines/2; i++)
    {
        float circleSize = i * 1.0f/w_lines + lineWidth/2;
        grid.arc(center, center, circleSize, circleSize, 0, 360);
        grid.arcNegative(center, center, circleSize - lineWidth, circleSize - lineWidth, 0, 360);
    }
    grid.close();
}

void Grid::arrows_translate()
{
    ofPushMatrix();
    ofTranslate(center, center);
    for (int i = 0; i < 2; ++i)
    {
        ofTriangle(baseSize/8, baseSize/2, 0, baseSize, -baseSize/8, baseSize/2);
        ofTriangle(-baseSize/8, -baseSize/2, 0, -baseSize, baseSize/8, -baseSize/2);
        ofRect(-baseSize/16, -baseSize/2, baseSize/8, baseSize);
        ofRotate(90, 0, 0, 1);
    }
    ofPopMatrix();
}

void Grid::arrows_rotate()
{
    ofPushMatrix();
    ofTranslate(center, center, 0);
    drawRotateArrow();
    ofPopMatrix();
}

void Grid::arrows_scale()
{
    // Right
    ofPushMatrix();
    ofTranslate(0.9, center, 0);
    scaleArrow.draw();
    ofPopMatrix();

    // Down
    ofPushMatrix();
    ofTranslate(center, 0.9, 0);
    ofRotate(90, 0, 0, 1);
    scaleArrow.draw();
    ofPopMatrix();

    // Left
    ofPushMatrix();
    ofTranslate(0.1, center, 0);
    ofRotate(180, 0, 0, 1);
    scaleArrow.draw();
    ofPopMatrix();

    // Up
    ofPushMatrix();
    ofTranslate(center, 0.1, 0);
    ofRotate(270, 0, 0, 1);
    scaleArrow.draw();
    ofPopMatrix();
}

void Grid::arrows_tilt()
{
    // Right
    ofPushMatrix();
    ofTranslate(1 - baseSize/2, center, 0);
    ofScale(0.5, 1, 1);
    drawRotateArrow();
    ofPopMatrix();

    // Down
    ofPushMatrix();
    ofTranslate(center, 1 - baseSize/2, 0);
    ofScale(1, 0.5, 1);
    drawRotateArrow();
    ofPopMatrix();

    // Left
    ofPushMatrix();
    ofTranslate(baseSize/2, center, 0);
    ofScale(0.5, 1, 1);
    drawRotateArrow();
    ofPopMatrix();

    // Up
    ofPushMatrix();
    ofTranslate(center, baseSize/2, 0);
    ofScale(1, 0.5, 1);
    drawRotateArrow();
    ofPopMatrix();
}

void Grid::drawRotateArrow()
{
    rotateArrow.draw();
    ofPushMatrix();
    ofRotate(30, 0, 0, 1);
    ofTranslate(baseSize - baseSize/10, 0, 0);
    ofTriangle(-3*baseSize/10, 0, 3*baseSize/10, 0, 0, -baseSize/2);
    ofPopMatrix();
}

