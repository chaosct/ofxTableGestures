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

#include "Figure.h"
#include "GlobalConfig.hpp"
#include "CollisionHelper.h"

using namespace Figures;

Figure::Figure():has_texture(false)
{
    bbox.Reset();
    matrix.SetIdentity();
}

Figure::~Figure()
{
    //dtor
}

void Figure::SetTexture(const std::string & path)
{
    if (path.compare("") == 0)
    {
        has_texture = false;
        return;
    }
    if(!texture.loadImage(path))
    {
        has_texture = false;
        return;
    }
    has_texture = true;
}

void Figure::SetTexture(ofImage& image)
{
    if(image.getHeight() == 0)
    {
        has_texture = false;
        return;
    }
    texture = image;
    has_texture = true;
}

void Figure::Draw()
{
    glGetDoublev(GL_MODELVIEW_MATRIX,matrix.data);
    if(CollisionHelper::debug_graphics)
    {
        bbox.Draw();
        ofNoFill();
        ofSetLineWidth(1.0f);
    }
    Design();
    if(CollisionHelper::debug_graphics)
        ofFill();

}

void Figure::DrawStroke()
{
    glGetDoublev(GL_MODELVIEW_MATRIX,matrix.data);
    DesignStroke();
    if(CollisionHelper::debug_graphics)
        bbox.Draw();
}

bool Figure::Collide(ofPoint const & point)
{
    ofPoint target = (CollisionHelper::ignore_transformation_matrix*matrix).TransformInverse(point);
    //std::cout << (CollisionHelper::ignore_transformation_matrix*matrix).ToString() << std::endl;
    //if(bbox.Collide(target.x,target.y) && CheckCollision(target))return true;
    //std::cout << target.x << " " << target.y << " -- " << point.x << " " << point.y << std::endl;
    if(bbox.Collide(target.x,target.y))
        if(CheckCollision(target))
            return true;
    return false;
}

ofPoint Figure::GetCentre()
{
    ofPoint center;
    /*center.x = 0;
    center.y = 0;
    center.z = 0;*/
    GetCentre(center.x,center.y);
    return matrix.Transform(center);
}

void Figure::GetCentre(float & x, float & y)
{
    ofPoint center;
    center.x = 0;
    center.y = 0;
    center.z = 0;
    matrix.Transform(center);
    x = center.x;
    y = center.y;
}
