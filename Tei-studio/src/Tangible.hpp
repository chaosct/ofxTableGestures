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
#include "InputGestureDirectObjects.h"
#include "InputGestureObjectFinger.h"


template< int figure_id>
class Tangible:public tuio::CanObjectFinger < tuio::CanDirectObjects < Graphic > >
{
    private:
        tuio::DirectObject * data;
        bool enable;
    public:
        Tangible():enable(false){
        }
        virtual ~Tangible(){}
        virtual tuio::DirectObject& GetPoint(){return *data;}
        virtual bool IsEnabled(){return enable;}
    protected:
        void Enable(bool flag = true){enable = flag;}
        ///Graphic methods
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
    public:
        ///CanDirectObjects methods
        virtual void newObject(int32 s_id, int32 f_id, tuio::DirectObject * object){
            if( figure_id == f_id){
                data = object;
                Enable(true);
            }
        }
        virtual void removeObject(int32 s_id, int32 f_id){
            if( figure_id == f_id ){
                //data = NULL //???
                Enable(false);
            }
        }
        ///CanObjectFinger methods
        virtual void objectFingerAdd(tuio::DirectObject* obj, tuio::DirectFinger* finger) {}
        virtual void objectFingerUpdate(tuio::DirectObject* obj, tuio::DirectFinger* finger) {}
        virtual void objectFingerRemove(tuio::DirectObject* obj, tuio::DirectFinger* finger) {}
        virtual void objectFingerTap(tuio::DirectObject* obj, float x, float y) {}
};

template <class Base, int triangle_distance>
class ShowAngleArrow:public Base
{
    public:
    virtual tuio::DirectObject& GetPoint(){return Base::GetPoint();}
    virtual bool IsEnabled(){return Base::IsEnabled();}
    protected:
    virtual void draw(){
        if(IsEnabled()){
            ofPushMatrix();
            ofTranslate(GetPoint().xpos*ofGetWidth(), GetPoint().ypos*ofGetHeight());
            ofRotate(GetPoint().angle*180/M_PI);
            ofTranslate(0,triangle_distance);
            ofSetColor(0xFFFFFF);
            ofTriangle(-7,5,0,0,7,5);
            ofPopMatrix();
            Base::draw();
        }
    }
};

#include "Tangible-ShowObjectSlider.h"

#endif // TANGIBLE_HPP_INCLUDED
