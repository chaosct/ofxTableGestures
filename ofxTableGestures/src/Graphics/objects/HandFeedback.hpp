/*

    OF-TangibleFramework . Framework for Taller de Sistemes Interactius I
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

class HandFeedback: public OnTable< tuio::CanHands< NotificationGraphic > >
{
    std::map<unsigned int,tuio::Hand *> hands;
    public:
    //Interface redefined by ofApp
    void newHand(tuio::Hand * p)
    {
        hands[p->id] = p;
    }
    void removeHand(tuio::Hand * p)
    {
        hands.erase(p->id);
    }
    void updateHand(tuio::Hand * p){}
    void draw()
    {
        ofSetColor(255,255,255);
        ofNoFill();
        std::pair<unsigned int,tuio::Hand *> p;
        BOOST_FOREACH(p,hands)
        {
            tuio::Hand * h = p.second;
            ofCircle(h->center.getX(),h->center.getY(),h->radius);
            ofLine(h->getX()-0.01f,h->getY()-0.01f,h->getX()+0.01f,h->getY()+0.01f);
            ofLine(h->getX()-0.01f,h->getY()+0.01f,h->getX()+0.01f,h->getY()-0.01f);
        }
    }
};

#endif // HANDFEEDBACK_HPP_INCLUDED
