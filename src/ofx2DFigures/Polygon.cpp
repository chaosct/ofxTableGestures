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

#include "Polygon.h"
#include "CollisionHelper.h"
#include "ofMain.h"
#include "Triangulate.h"

using namespace Figures;
using namespace std;

Polygon::Polygon()
{

}

Polygon::Polygon(vector_points):processed(false),it_is_empty(true)
{
    centre = ofPoint(-1.0,-1.0);
}

void Polygon::AddVertex(ofPoint vertex)
{
    raw_vertexs.push_back(vertex);
    bbox.AddPoint(vertex.x,vertex.y);
    if(it_is_empty)
    {
        centre = ofPoint(vertex);
    }
    else
    {
        centre += vertex;
        centre = centre / 2;
    }
    processed = false;
}

void Polygon::RebuildGeometry()
{
    if(raw_vertexs.size() >= 3)
    {
        updatedVertexs.clear();
        Triangulate::Process(raw_vertexs,updatedVertexs);
    }
}

int Polygon::GetTriangleNumber()
{
    if (!processed) RebuildGeometry();
    return updatedVertexs.size()/3;
}

void Polygon::Design()
{
    if (!processed) RebuildGeometry();
    ofPushMatrix();
    int tcount = updatedVertexs.size()/3;
    for (int i=0; i<tcount; i++)
    {
        ofBeginShape();
        ofVertex(updatedVertexs[i*3+0].x,updatedVertexs[i*3+0].y);
        ofVertex(updatedVertexs[i*3+1].x,updatedVertexs[i*3+1].y);
        ofVertex(updatedVertexs[i*3+2].x,updatedVertexs[i*3+2].y);
        ofEndShape();
    }
    ofPopMatrix();
}

void Polygon::DesignStroke()
{
    ofPushMatrix();
    for(unsigned int i = 0; i < raw_vertexs.size(); i++)
    {
        if( i+1 < raw_vertexs.size())
            ofLine(raw_vertexs[i].x,raw_vertexs[i].y,raw_vertexs[i+1].x,raw_vertexs[i+1].y);
        else
            ofLine(raw_vertexs[i].x,raw_vertexs[i].y,raw_vertexs[0].x,raw_vertexs[0].y);
    }
    ofPopMatrix();
}

bool Polygon::CheckCollision(ofPoint const & point)
{
    if (!processed) RebuildGeometry();
    int tcount = updatedVertexs.size()/3;
    for (int i=0; i<tcount; i++)
    {
        if(CollisionHelper::CollideTriangle(updatedVertexs[i*3+0],updatedVertexs[i*3+1],updatedVertexs[i*3+2],point.x, point.y))
            return true;
    }
    return false;
}

void Polygon::GetCentre(float & x, float & y)
{
    x = centre.x;
    y = centre.y;
}

