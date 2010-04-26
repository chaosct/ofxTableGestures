#ifndef BUTTON_HPP_INCLUDED
#define BUTTON_HPP_INCLUDED

#include "InputGestureDirectFingers.hpp"
#include "Graphic.hpp"
#include <set>

class Button : public tuio::CanDirectFingers< Graphic >
{
    std::set<tuio::DirectFinger *> fingers;
    public:
    Button(Area * a)
    {
      this->Register(a);
    }
    void newCursor(tuio::DirectFinger * f){if (!IsPressed())OnPush(); fingers.insert(f);}
    void removeCursor(tuio::DirectFinger *f){fingers.erase(f); if (!IsPressed())OnRelease();}
    //ignore cursors not appearing directly
    void enterCursor(tuio::DirectFinger *){}

    bool IsPressed(){return fingers.size() > 0;}

    virtual void OnPush(){}
    virtual void OnRelease(){}
};

class CircleButton: public Button
{
    public:
    CircularArea a;
    float & x;
    float & y;
    float & r;
    CircleButton():Button(&a),x(a.x),y(a.y),r(a.r)
    {
        x = 0.5;
        y = 0.5;
        r = 0.03;
    }
    virtual void draw()
    {
        if(IsPressed())
            ofSetColor(255,100,100);
        else
            ofSetColor(255,0,0);
        ofCircle(x,y,r);
    }
};

#endif // BUTTON_HPP_INCLUDED
