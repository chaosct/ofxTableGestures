#include "InputGestureDirectFingers.hpp"

ofEvent<InputGestureDirectFingers::removeCursorArgs> InputGestureDirectFingers::removeCursor;
ofEvent<InputGestureDirectFingers::newCursorArgs> InputGestureDirectFingers::newCursor;
ofEvent<InputGestureDirectFingers::updateCursorArgs> InputGestureDirectFingers::updateCursor;
ofEvent<InputGestureDirectFingers::enterCursorArgs> InputGestureDirectFingers::enterCursor;
ofEvent<InputGestureDirectFingers::exitCursorArgs> InputGestureDirectFingers::exitCursor;

InputGestureDirectFingers::InputGestureDirectFingers()
{
    registerEvent(InputGestureBasicFingers::addTuioCursor,&InputGestureDirectFingers::addTuioCursor);
    registerEvent(InputGestureBasicFingers::enterTuioCursor,&InputGestureDirectFingers::enterTuioCursor);
    registerEvent(InputGestureBasicFingers::updateTuioCursor,&InputGestureDirectFingers::updateTuioCursor);
    registerEvent(InputGestureBasicFingers::removeTuioCursor,&InputGestureDirectFingers::removeTuioCursor);
    registerEvent(InputGestureBasicFingers::exitTuioCursor,&InputGestureDirectFingers::exitTuioCursor);
}

void InputGestureDirectFingers::addTuioCursor(InputGestureBasicFingers::addTuioCursorArgs & a)
{
    DirectFinger * e = new DirectFinger();
    e->s_id = a.id;
    e->set(a.xpos, a.ypos);
    e->xspeed = a.xspeed;
    e->yspeed = a.yspeed;
    e->maccel = a.maccel;
    fingers[a.id]=e;
    newCursorArgs eventargs;
    eventargs.finger = e;
    eventargs.target = a.target;
    ofNotifyEvent(newCursor,eventargs);
}

void InputGestureDirectFingers::enterTuioCursor(InputGestureBasicFingers::enterTuioCursorArgs & a)
{
    DirectFinger * e = fingers[a.id];
    e->s_id = a.id;
    e->set(a.xpos, a.ypos);
    e->xspeed = a.xspeed;
    e->yspeed = a.yspeed;
    e->maccel = a.maccel;
    fingers[a.id]=e;
    enterCursorArgs eventargs;
    eventargs.finger = e;
    eventargs.target = a.target;
    ofNotifyEvent(enterCursor,eventargs);
}

void InputGestureDirectFingers::updateTuioCursor(InputGestureBasicFingers::updateTuioCursorArgs & a)
{
    DirectFinger * e = fingers[a.id];
    e->s_id = a.id;
    e->set(a.xpos,a.ypos);
    e->xspeed = a.xspeed;
    e->yspeed = a.yspeed;
    e->maccel = a.maccel;
    updateCursorArgs eventargs;
    eventargs.finger = e;
    eventargs.target = a.target;
    ofNotifyEvent(updateCursor,eventargs);
}

void InputGestureDirectFingers::removeTuioCursor(InputGestureBasicFingers::removeTuioCursorArgs & a)
{
    DirectFinger * e = fingers[a.id];
    removeCursorArgs eventargs;
    eventargs.finger = e;
    eventargs.target = a.target;
    ofNotifyEvent(removeCursor,eventargs);
}

void InputGestureDirectFingers::exitTuioCursor(InputGestureBasicFingers::exitTuioCursorArgs & a)
{
    DirectFinger * e = fingers[a.id];
    exitCursorArgs eventargs;
    eventargs.finger = e;
    eventargs.target = a.target;
    ofNotifyEvent(exitCursor,eventargs);

}
