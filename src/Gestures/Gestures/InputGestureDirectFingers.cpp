#include "InputGestureDirectFingers.hpp"

InputGestureDirectFingers::InputGestureDirectFingers()
{
    registerEvent(InputGestureBasicFingers::Instance().addTuioCursor,&InputGestureDirectFingers::addTuioCursor);
    registerEvent(InputGestureBasicFingers::Instance().enterTuioCursor,&InputGestureDirectFingers::enterTuioCursor);
    registerEvent(InputGestureBasicFingers::Instance().updateTuioCursor,&InputGestureDirectFingers::updateTuioCursor);
    registerEvent(InputGestureBasicFingers::Instance().removeTuioCursor,&InputGestureDirectFingers::removeTuioCursor);
    registerEvent(InputGestureBasicFingers::Instance().exitTuioCursor,&InputGestureDirectFingers::exitTuioCursor);
}

void InputGestureDirectFingers::addTuioCursor(InputGestureBasicFingers::addTuioCursorArgs & a)
{

    DirectFinger * e = new DirectFinger();
    e->s_id = a.id;
    e->setX(a.xpos);
    e->setY(a.ypos);
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
    e->setX(a.xpos);
    e->setY(a.ypos);
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
