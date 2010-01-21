/*
    TSIframework . Framework for Taller de Sistemes Interactius I
    Universitat Pompeu Fabra

    Copyright (c) 2009 Daniel Gallardo Grassot <daniel.gallardo@upf.edu>

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

#ifndef TANGIBLE_HPP_INCLUDED
#define TANGIBLE_HPP_INCLUDED
#include "Graphic.hpp"
#include "DirectPoint.h"
#include "Shapes.hpp"
#include "tuioApp.h"
#include "InputGestureBasicObjects.h"

class Tangible:public tuio::CanBasicObjects < Graphic >
{
    private:
        int fid;
        float angle;
        DirectPoint p;
        bool enable;
    public:
        Tangible(int _fid):fid(_fid),angle(0),enable(false){}
        virtual ~Tangible(){}
        DirectPoint& GetPoint(){return p;}
        float GetAngle(){return angle;}
        void Set(float x, float y, float _angle){
            angle = _angle;
            p.xpos = x;
            p.ypos = y;
        }
    protected:
        void Enable(bool flag = true){enable = flag;}
        virtual void draw(){
            ///not needed, it is drawn by FigureFeedback
//            ofPushMatrix();
//            ofTranslate(p.xpos,p.ypos);
//            ofRotate(angle*180/M_PI);
//            shapes::Figure_shape::Instance().drawShape(fid);
//            ofPopMatrix();
        }
        virtual void update(){}
        virtual void resize(int x, int y){}
};

#endif // TANGIBLE_HPP_INCLUDED
