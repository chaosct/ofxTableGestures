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

#include "BoundingBox.h"

using namespace Figures;

BoundingBox::BoundingBox():setedup(false)
{
    Reset();
}

void BoundingBox::Reset()
{
    xmin = 0;    xmax = 0;
    ymin = 0;
    ymax = 0;
    setedup = false;
}

void BoundingBox::AddPoint(float x, float y)
{
    if(!setedup)
    {
        setedup = true;
        xmin = x;
        xmax = x;
        ymin = y;
        ymax = y;
    }
}

bool BoundingBox::Collide(float x, float y)
{
    if( !setedup ) return false;
    if( x >= xmin && x <= xmax && y >= ymin && y <= ymax) return true;
    return false;
}

void BoundingBox::Draw()
{
    // to do
}
