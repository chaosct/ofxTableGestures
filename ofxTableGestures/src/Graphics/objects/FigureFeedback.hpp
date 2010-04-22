/*

    OF-TangibleFramework . Framework for Taller de Sistemes Interactius I
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

#ifndef FIGUREFEEDBACK_H_INCLUDED
#define FIGUREFEEDBACK_H_INCLUDED

#include "ofMain.h"
#include "tuioApp.hpp"
#include "InputGestureDirectObjects.hpp"
#include <map>
#include "Shapes.hpp"
#include "Graphic.hpp"
#include "DirectPoint.hpp"

class HistoryFigure{
    public:
        tuio::DirectObject * dobj;
        float released_time;
        float scale_factor;
        float & OBJECT_DISAPPEAR_TIME;
        HistoryFigure(tuio::DirectObject * obj):
            dobj(obj),
            OBJECT_DISAPPEAR_TIME(GlobalConfig::getRef("FEEDBACK:FIGURE:DISAPPEAR",0.25f)),
            scale_factor(1){}
        void Release(float time){
            released_time = time;
        }
        void Update(float time){
            float elapsed = time - released_time;
            scale_factor = 1-(float)elapsed / (float)OBJECT_DISAPPEAR_TIME;
            if (scale_factor <= 0)scale_factor = 0;
        }
        bool CanDelete(){
            if (scale_factor <= 0) return true;
            return false;
        }
        void draw(){
            ofPushMatrix();
            ofTranslate(dobj->getX()*ofGetWidth(),dobj->getY()*ofGetHeight());
            ofRotate(dobj->angle*180/M_PI);
            ofScale(scale_factor,scale_factor,1);
            shapes::Figure_shape::Instance().drawShape(dobj->f_id);
            ofPopMatrix();
        }
};

class FigureFeedback: public tuio::CanDirectObjects < NotificationGraphic > {
        std::map<int32,HistoryFigure*> objects;
        std::list<HistoryFigure*> to_delete;
    public:
        FigureFeedback();
        FigureFeedback(Area * a);
        ~FigureFeedback();
        void newObject(tuio::DirectObject * object);
        void removeObject(tuio::DirectObject * object);
    protected:
        void draw();
        void update();
};

#endif // FIGUREFEEDBACK_H_INCLUDED
