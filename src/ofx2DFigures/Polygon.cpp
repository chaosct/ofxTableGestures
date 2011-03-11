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

using namespace Figures;
using namespace std;

Polygon::Polygon()
{

}

Polygon::Polygon(vector_points)
{

}

void Polygon::AddVertex(ofPoint vertex)
{
    raw_vertexs.push_back(vertex);
    bbox.AddPoint(vertex.x,vertex.y);
    centre += vertex;
    centre = centre / 2;
    processed = false;
}

void Polygon::RebuildGeometry()
{

}

void Polygon::Design()
{

}

void Polygon::DesignStroke()
{

}

bool Polygon::CheckCollision(ofPoint const & point)
{
    return false;
}

void Polygon::GetCentre(float & x, float & y)
{
    x = centre.x;
    y = centre.y;
}
