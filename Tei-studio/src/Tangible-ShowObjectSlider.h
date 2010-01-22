#ifndef TANGIBLE_SHOWOBJECTSLIDER_H_INCLUDED
#define TANGIBLE_SHOWOBJECTSLIDER_H_INCLUDED


//assume 0->pi
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
            sliderValue = currentAngle / PI;
        }
    }

    public:
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
