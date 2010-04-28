/*

    TSIframework . Framework for Taller de Sistemes Interactius I
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

///----------------------------------------------------------------------------------------
///                                BUTTON MADNESS TEST
///----------------------------------------------------------------------------------------
///             USAGE:
///                 new ButtonMadnessTest();
///
///     It creates new buttons with new areas when pushing them. Used to test the massive
///     creation and computatation of areas.
///----------------------------------------------------------------------------------------

#ifndef BUTTONMADNESSTEST_HPP_INCLUDED
#define BUTTONMADNESSTEST_HPP_INCLUDED
#include "Button.hpp"
class ButtonMadnessTest : public CircleButton
{
    protected:
    float vx,vy;
    bool candelete;
    public:
    ButtonMadnessTest():vx(0.001),vy(0.002),candelete(false){}
    void update()
    {
        if(candelete)
        {
            delete this;
            return;
        }
        x += vx;
        y += vy;
        if(x > 1 || x < 0)
            vx = -vx;
        if(y > 1 || y < 0)
            vy = -vy;
    }
    void draw()
    {
        ofEnableAlphaBlending();
        if(IsPressed())
            ofSetColor(255,100,100,100);
        else
            ofSetColor(255,0,0,100);
        ofCircle(x,y,r);
        ofDisableAlphaBlending();
    }
    void OnPush()
    {
        ButtonMadnessTest * b = new ButtonMadnessTest();
        b->vx = ofRandom(-0.005,0.005f);
        b->vy = ofRandom(-0.005,0.005f);
        b->x = x;
        b->y = y;
        b->r = ofRandom(0.01f,0.05f);
        //candelete = true;
    }
};

#endif // BUTTONMADNESSTEST_HPP_INCLUDED
