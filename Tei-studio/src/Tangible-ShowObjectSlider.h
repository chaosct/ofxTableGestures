/*

    OF-TangibleFramework . Framework for Taller de Sistemes Interactius I
    Universitat Pompeu Fabra

    Copyright (c) 2009 Carles F. Julià <carles.fernandez@upf.edu>

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

#ifndef TANGIBLE_SHOWOBJECTSLIDER_H_INCLUDED
#define TANGIBLE_SHOWOBJECTSLIDER_H_INCLUDED

/**
// Summary
template <class Base>
class ShowObjectSlider : public Base
{
public:

    ///Interface to implement
    virtual void sliderValueUpdated(double newvalue){}

    //accessor to slider value
    double getSliderValue();

    ShowObjectSlider();

    //reimplements Tangible
    virtual void objectFingerAdd(tuio::DirectObject* obj, tuio::DirectFinger* finger);
    virtual void objectFingerRemove(tuio::DirectObject* obj, tuio::DirectFinger* finger);
    virtual void objectFingerUpdate(tuio::DirectObject* obj, tuio::DirectFinger* finger);
    protected:
    virtual void draw();
};

*/


template <class Base>
class ShowObjectSlider : public Base
{
    private:
    std::list<DirectPoint> arc;
    int color;
    int linewidth;
    double radius;
    tuio::DirectFinger * df;
    double sliderValue;
    double currentAngle;

    void updateValue ()
    {
        currentAngle = Base::GetPoint().getAngle(df) - Base::GetPoint().angle;
        if(currentAngle < 0) currentAngle += 2*PI;
        if(currentAngle > 0 && currentAngle < PI)
        {
            double oldvalue = sliderValue;
            sliderValue = currentAngle / PI;
            if(oldvalue != sliderValue)
                sliderValueUpdated(sliderValue); //Calling the interface
        }
    }

    public:

    ///Interface to implement
    virtual void sliderValueUpdated(double newvalue){}

    ShowObjectSlider():color(0x0010EE),linewidth(5),radius(50),df(NULL),sliderValue(0)
    {
        DirectPoint p;
        //build Arc
        double step = PI/20.0;
        for (double i = 0; i <= PI; i+=step)
        {
            arc.push_back(DirectPoint(cos(i),sin(i)));
        }
    }
    double getSliderValue(){return sliderValue;}
    virtual void objectFingerAdd(tuio::DirectObject* obj, tuio::DirectFinger* finger)
    {
        Base::objectFingerAdd(obj,finger);
        if(Base::IsEnabled() && obj->s_id == Base::GetPoint().s_id && !df)
        {
            df = finger;
            updateValue();
        }
    }
    virtual void objectFingerRemove(tuio::DirectObject* obj, tuio::DirectFinger* finger)
    {
        Base::objectFingerRemove(obj, finger);
        if(Base::IsEnabled() && obj->s_id == Base::GetPoint().s_id && df && df->s_id == finger->s_id)
        {
            df = NULL;
        }
    }
    virtual void objectFingerUpdate(tuio::DirectObject* obj, tuio::DirectFinger* finger)
    {
        Base::objectFingerUpdate(obj,finger);
        if(Base::IsEnabled() && obj->s_id == Base::GetPoint().s_id && df && df->s_id == finger->s_id)
        {
            updateValue();
        }
    }
    protected:
    virtual void draw(){
        if(Base::IsEnabled()){
            ofPushMatrix();
            ofTranslate(Base::GetPoint().xpos*ofGetWidth(), Base::GetPoint().ypos*ofGetHeight());
            ofRotate(Base::GetPoint().angle*180/M_PI);
            ofSetColor(color);
            ofSetLineWidth(linewidth);
            glBegin(GL_LINE_STRIP);
            for (std::list<DirectPoint>::iterator it = arc.begin(); it != arc.end(); it++)
            {
                glVertex2f(radius*it->getX(),radius*it->getY());
            }
            glEnd();
            double a = sliderValue *  PI;
            ofCircle(cos(a)*radius,sin(a)*radius,10);
            ofPopMatrix();
            Base::draw();
        }
    }
};


#endif // TANGIBLE_SHOWOBJECTSLIDER_H_INCLUDED
