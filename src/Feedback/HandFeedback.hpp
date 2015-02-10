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

#ifndef HANDFEEDBACK_HPP_INCLUDED
#define HANDFEEDBACK_HPP_INCLUDED

#include "InputGestureHand.hpp"

class HandFeedback: public FeedbackGraphic
{
    std::map<unsigned int,Hand *> hands;
    InputGestureHands igh;
    public:

    void newHand(InputGestureHands::newHandArgs & a)
    {
        hands[a.hand->id] = a.hand;
    }
    void removeHand(InputGestureHands::removeHandArgs & a)
    {
        hands.erase(a.hand->id);
    }
    void draw()
    {
        ofSetColor(255,255,255);
        ofNoFill();
        for (std::map<unsigned int,Hand *>::iterator it = hands.begin(); it != hands.end(); ++it)
        {
            Hand * h = it->second;
            ofCircle(h->center.x, h->center.y, h->radius);
            ofLine(h->x-0.01f, h->y-0.01f, h->x+0.01f, h->y+0.01f);
            ofLine(h->x-0.01f, h->y+0.01f, h->x+0.01f, h->y-0.01f);
        }
    }
    HandFeedback(Graphic * target): igh(target)
    {
        registerEvent(igh.newHand, &HandFeedback::newHand);
        registerEvent(igh.removeHand, &HandFeedback::removeHand);
    }
};

#endif // HANDFEEDBACK_HPP_INCLUDED
