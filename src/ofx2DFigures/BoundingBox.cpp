#include "BoundingBox.h"

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
