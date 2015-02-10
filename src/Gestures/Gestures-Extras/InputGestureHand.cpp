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

#include "InputGestureHand.hpp"


ofVec2f Hand::getCenter()
{
    ofVec2f p(0);
    if(fingers.size() < 1)
        return p;
    float x = 0;
    float y = 0;
    for(std::list<DirectFinger *>::iterator it = fingers.begin(); it != fingers.end(); ++it)
    {
        x += (*it)->x;
        y += (*it)->y;
    }
    p.set(x/fingers.size(), y/fingers.size());
    return p;
}

float Hand::getRadius()
{
    float distance = 0;
    for(std::list<DirectFinger *>::iterator it = fingers.begin(); it != fingers.end(); ++it)
    {
        ofVec2f* f = *it;
        distance = std::max(f->distance(this->center),distance);
    }
    return distance;
}

bool Hand::isValid()
{
    return fingers.size() >= 1;
}

Hand * InputGestureHands::getNeighbour(ofVec2f * p, Hand * ignore)
{
    Hand * winner = NULL;
    float dwinner = 1000;
    for(std::list<Hand *>::iterator it = hands.begin(); it != hands.end(); ++it)
    {
        Hand *h = *it;
        if (h->is_valid && h != ignore)
        {
            float d = h->center.distance(*p);
            if (d < HAND_MAX_RADIUS && d < dwinner)
            {
                dwinner = d;
                winner = h;
            }
        }
    }
    return winner;
}

void InputGestureHands::newCursor(InputGestureDirectFingers::newCursorArgs & a)
{
    DirectFinger * df = a.finger;
    Hand * winner = getNeighbour(df);
    if (!winner)
    {
        winner = new Hand(hands.size());
        hands.push_back(winner);
        assignations[df->s_id]=winner;
        winner->fingers.push_back(df);
        winner->UpdateExposedInfo();
        newHandArgs eventargs;
        eventargs.hand = winner;
        ofNotifyEvent(newHand,eventargs);

    }
    else
    {
        assignations[df->s_id]=winner;
        winner->fingers.push_back(df);
        winner->UpdateOffset();
        winner->UpdateExposedInfo();
        updateHandArgs eventargs;
        eventargs.hand = winner;
        ofNotifyEvent(updateHand,eventargs);

    }
}

void InputGestureHands::removeCursor(InputGestureDirectFingers::removeCursorArgs & a)
{
    DirectFinger * f = a.finger;
    Hand * h = assignations[f->s_id];
    h->fingers.remove(f);
    h->UpdateOffset();
    h->UpdateExposedInfo();
    if (!h->is_valid)
    {
        removeHandArgs eventargs;
        eventargs.hand = h;
        ofNotifyEvent(removeHand,eventargs);

    }
    else
    {
        updateHandArgs eventargs;
        eventargs.hand = h;
        ofNotifyEvent(updateHand,eventargs);

    }

}

void InputGestureHands::updateCursor(InputGestureDirectFingers::updateCursorArgs & a)
{
    DirectFinger * f = a.finger;
    Hand * h = assignations[f->s_id];
    h->UpdateExposedInfo();
    updateHandArgs eventargs;
    eventargs.hand = h;
    ofNotifyEvent(updateHand,eventargs);

    if(h->population == 1)
    {
        Hand * candidate = getNeighbour(f,h);
        if(candidate)
        {
            h->fingers.remove(f);
            h->UpdateOffset();
            h->UpdateExposedInfo();
            {


                removeHandArgs eventargs;
                eventargs.hand = h;
                ofNotifyEvent(removeHand,eventargs);
            }

            assignations[f->s_id]=candidate;
            candidate->fingers.push_back(f);
            candidate->UpdateOffset();
            candidate->UpdateExposedInfo();
            {


                updateHandArgs eventargs;
                eventargs.hand = candidate;
                ofNotifyEvent(updateHand,eventargs);
            }

        }
    }
    else if(h->distance(*f) > HAND_MAX_RADIUS)
    {
        h->fingers.remove(f);
        h->UpdateOffset();
        h->UpdateExposedInfo();
        this->newCursor(a);
    }
}

