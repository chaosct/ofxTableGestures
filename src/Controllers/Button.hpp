/*

    ofxTableGestures (formerly OF-TangibleFramework)
    Developed for Taller de Sistemes Interactius I
    Universitat Pompeu Fabra

    Copyright (c) 2010 Carles F. Julià <carles.fernandez@upf.edu>

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

#ifndef BUTTON_HPP_INCLUDED
#define BUTTON_HPP_INCLUDED

#include "InputGestureDirectFingers.hpp"
#include "InputGestureTap.hpp"
#include "Graphic.hpp"
#include <set>

class Button : public tuio::CanTap < tuio::CanDirectFingers< Graphic > >
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

    void Tap(float x, float y){OnTap();}

    bool IsPressed(){return fingers.size() > 0;}

    virtual void OnPush(){}
    virtual void OnRelease(){}
    virtual void OnTap(){}
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
