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
        Tangible():enable(false),data(NULL){
        }
        virtual ~Tangible(){}
        virtual tuio::DirectObject& GetPoint(){return *data;}
        virtual bool IsEnabled(){return enable;}
    protected:
        virtual void Enable(bool flag = true){enable = flag;}
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
            if( !data && figure_id == f_id){
                data = object;
                Enable(true);
            }
        }
        virtual void removeObject(int32 s_id, int32 f_id){
            if( data && figure_id == f_id ){
                data = NULL;
                Enable(false);
            }
        }
        float getAngleDegrees(){
            return GetPoint().angle*180/M_PI;
        }
        ///CanObjectFinger methods
        virtual void objectFingerAdd(tuio::DirectObject* obj, tuio::DirectFinger* finger) {}
        virtual void objectFingerUpdate(tuio::DirectObject* obj, tuio::DirectFinger* finger) {}
        virtual void objectFingerRemove(tuio::DirectObject* obj, tuio::DirectFinger* finger) {}
        virtual void objectFingerTap(tuio::DirectObject* obj, float x, float y) {}
};

template <class Base , int spins=0, int min_degrees= -1 ,int max_degrees=-1>
class SpinsPerAngle: public tuio::CanBasicObjects < Base >{
    private:
        float angle;
        float previous_angle;
        float _spins;
        int min, max;
        bool loop;
        void resetMinMax(){min =0;max=360;loop=true;}
    public:
        SpinsPerAngle():angle(0),previous_angle(0),_spins(spins),min(min_degrees),max(max_degrees),loop(false){
            SetSpinParameters(_spins,min,max);
        }
        void SetSpinParameters(int sp=0, int min_deg=-1, int max_deg=-1){
            _spins = sp;
            min = min_deg;
            max = max_deg;
            if (min == -1 || max == -1 || min == max) resetMinMax();
            else if(min > max){
                int tmp=min;
                min = max;
                max = tmp;
            }
            if (_spins <= 0) _spins = 1;
        }
        virtual void addTuioObject(int32 id, int32 f_id ,float xpos,float ypos, float _angle, float xspeed,float yspeed,float rspeed,float maccel, float raccel){
            previous_angle = _angle;
        }
        virtual void updateTuioObject(int32 id, int32 f_id ,float xpos,float ypos, float _angle, float xspeed,float yspeed,float rspeed,float maccel, float raccel){
            float increment = previous_angle-_angle;
            if(increment >= M_PI) increment = increment - TWO_PI;
            else if (increment < -M_PI) increment = increment + TWO_PI;
            angle -= increment;
            //if(angle >= TWO_PI) angle -= TWO_PI;
            //else if (angle < 0) angle += TWO_PI;
            previous_angle = _angle;
        }
        float getAngleDegrees(){
            float tmp_angle = (angle/_spins);
            float toreturn = tmp_angle*180/M_PI;
            if(!loop){
                if (toreturn > max) return max;
                else if(toreturn < min) return min;
            }
            return toreturn;
        }
       virtual int getMaxValue(){return max;}
       virtual int getMinValue(){return min;}
};
//Show limited angle arrow template class from, to
template <class Base, int triangle_distance>
class ShowAngleArrow:public /*SpinsPerAngle <*/ Base /*>*/
{
    public:
    virtual tuio::DirectObject& GetPoint(){return Base::GetPoint();}
    virtual bool IsEnabled(){return Base::IsEnabled();}
    virtual float getAngleDegrees(){return Base::getAngleDegrees();}
    protected:
    virtual void draw(){
        if(IsEnabled()){
            ofPushMatrix();
            ofTranslate(GetPoint().xpos*ofGetWidth(), GetPoint().ypos*ofGetHeight());
            ofRotate(getAngleDegrees());
            ofTranslate(0,triangle_distance);
            ofSetColor(0xFFFFFF);
            ofTriangle(-7,5,0,0,7,5);
            ofPopMatrix();
            Base::draw();
        }
    }
};

template <class Base, int from=-1, int to=-1>
class ShowAngleArrowWithMarks: public /*ShowAngleArrow <*/ Base /*, 50 >*/
{
    public:
        ShowAngleArrowWithMarks(){
        }
        virtual bool IsEnabled(){return Base::IsEnabled();}
        virtual tuio::DirectObject& GetPoint(){return Base::GetPoint();}
        virtual float getAngleDegrees(){return Base::getAngleDegrees();}
        virtual int getMaxValue(){return Base::getMaxValue();}
        virtual int getMinValue(){return Base::getMinValue();}
        virtual void draw(){
            if(IsEnabled()){
                ofPushMatrix();
                ofTranslate(GetPoint().xpos*ofGetWidth(), GetPoint().ypos*ofGetHeight());
                ofPushMatrix();
                ofRotate(getAngleDegrees());
                ofTranslate(0,50);
                ofSetColor(0xFFFFFF);
                ofTriangle(-7,5,0,0,7,5);
                ofPopMatrix();
                ofPushMatrix();
                double step = PI/20.0;
                float radius = 50;
                ofSetLineWidth(1);
                ofRotate(90);
                glBegin(GL_LINE_STRIP);
                for (double i = (float)getMinValue()*M_PI/180.0f; i <= (float)getMaxValue()*M_PI/180.0f; i+=step)
                {
                    glVertex2f(radius*cos(i),radius*sin(i));
                }
                glEnd();
                ofPopMatrix();

                ofPushMatrix();
                ofSetColor(255,0,0);
                ofRotate((float)getMinValue());
                ofTranslate(0,50);
                ofRect(0,0,3,5);
                ofPopMatrix();

                ofPushMatrix();
                ofSetColor(0,255,0);
                ofRotate((float)getMaxValue());
                ofTranslate(0,50);
                ofRect(0,0,3,5);
                ofPopMatrix();

                ofPopMatrix();
                Base::draw();
            }
        }
};

#include "Tangible-ShowObjectSlider.h"

#endif // TANGIBLE_HPP_INCLUDED
