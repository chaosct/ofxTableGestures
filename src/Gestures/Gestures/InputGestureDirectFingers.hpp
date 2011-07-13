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

#ifndef INPUTGESTUREDIRECTFINGERS_H_INCLUDED
#define INPUTGESTUREDIRECTFINGERS_H_INCLUDED


#include "DirectPoint.hpp"
#include "InputGestureBasicFingers.hpp"
#include <map>


class DirectFinger: public DirectPoint
{
public:
    int s_id;
    float xspeed, yspeed, maccel;
};



class InputGestureDirectFingers : public EventClient, public Singleton<InputGestureDirectFingers>
{
    std::map<int,DirectFinger *> fingers;
public:
    struct commonDirectFingerArgs: public EventArgs
    {
        DirectFinger * finger;
    };

    typedef commonDirectFingerArgs newCursorArgs;
    typedef commonDirectFingerArgs removeCursorArgs;
    typedef commonDirectFingerArgs updateCursorArgs;
    typedef commonDirectFingerArgs enterCursorArgs;
    typedef commonDirectFingerArgs exitCursorArgs;

    ofEvent<removeCursorArgs> removeCursor;
    ofEvent<newCursorArgs> newCursor;
    ofEvent<updateCursorArgs> updateCursor;
    ofEvent<enterCursorArgs> enterCursor;
    ofEvent<exitCursorArgs> exitCursor;

    InputGestureDirectFingers();
    void addTuioCursor(InputGestureBasicFingers::addTuioCursorArgs & a);
    void enterTuioCursor(InputGestureBasicFingers::enterTuioCursorArgs & a);
    void updateTuioCursor(InputGestureBasicFingers::updateTuioCursorArgs & a);
    void removeTuioCursor(InputGestureBasicFingers::removeTuioCursorArgs & a);
    void exitTuioCursor(InputGestureBasicFingers::removeTuioCursorArgs & a);
};


/*

template <class Base>
class CanDirectFingers : public  Base
{
public:
    void EnewCursor(InputGestureDirectFingers::newCursorArgs & eventargs)
    {
        newCursor(eventargs.finger);
    }
    virtual void newCursor(DirectFinger * finger) {}
    void EremoveCursor(InputGestureDirectFingers::removeCursorArgs & eventargs)
    {
        removeCursor(eventargs.finger);
    }
    virtual void removeCursor(DirectFinger * finger) {}
    void EupdateCursor(InputGestureDirectFingers::updateCursorArgs & eventargs)
    {
        updateCursor(eventargs.finger);
    }
    virtual void updateCursor(DirectFinger * finger) {}
    void EenterCursor(InputGestureDirectFingers::enterCursorArgs & eventargs)
    {
        enterCursor(eventargs.finger);
    }
    virtual void enterCursor(DirectFinger *finger)
    {
        newCursor(finger);
    }
    void EexitCursor(InputGestureDirectFingers::exitCursorArgs & eventargs)
    {
        exitCursor(eventargs.finger);
    }
    virtual void exitCursor(DirectFinger *finger)
    {
        removeCursor(finger);
    }

    CanDirectFingers()
    {
        ofAddListener(InputGestureDirectFingers::Instance().newCursor,this,&CanDirectFingers::EnewCursor);
        ofAddListener(InputGestureDirectFingers::Instance().removeCursor,this,&CanDirectFingers::EremoveCursor);
        ofAddListener(InputGestureDirectFingers::Instance().updateCursor,this,&CanDirectFingers::EupdateCursor);
        ofAddListener(InputGestureDirectFingers::Instance().enterCursor,this,&CanDirectFingers::EenterCursor);
        ofAddListener(InputGestureDirectFingers::Instance().exitCursor,this,&CanDirectFingers::EexitCursor);
    }
    virtual ~CanDirectFingers()
    {
        ofRemoveListener(InputGestureDirectFingers::Instance().newCursor,this,&CanDirectFingers::EnewCursor);
        ofRemoveListener(InputGestureDirectFingers::Instance().removeCursor,this,&CanDirectFingers::EremoveCursor);
        ofRemoveListener(InputGestureDirectFingers::Instance().updateCursor,this,&CanDirectFingers::EupdateCursor);
        ofRemoveListener(InputGestureDirectFingers::Instance().enterCursor,this,&CanDirectFingers::EenterCursor);
        ofRemoveListener(InputGestureDirectFingers::Instance().exitCursor,this,&CanDirectFingers::EexitCursor);
    }

};

*/

#endif // INPUTGESTUREDIRECTFINGERS_H_INCLUDED
