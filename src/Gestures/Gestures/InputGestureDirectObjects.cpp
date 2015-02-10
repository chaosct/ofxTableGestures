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

#include "InputGestureDirectObjects.hpp"

ofEvent<InputGestureDirectObjects::newObjectArgs> InputGestureDirectObjects::newObject;
ofEvent<InputGestureDirectObjects::removeObjectArgs> InputGestureDirectObjects::removeObject;
ofEvent<InputGestureDirectObjects::updateObjectArgs> InputGestureDirectObjects::updateObject;
ofEvent<InputGestureDirectObjects::enterObjectArgs> InputGestureDirectObjects::enterObject;
ofEvent<InputGestureDirectObjects::exitObjectArgs> InputGestureDirectObjects::exitObject;

InputGestureDirectObjects::InputGestureDirectObjects()
{
    registerEvent(InputGestureBasicObjects::addTuioObject,&InputGestureDirectObjects::addTuioObject);
    registerEvent(InputGestureBasicObjects::enterTuioObject,&InputGestureDirectObjects::enterTuioObject);
    registerEvent(InputGestureBasicObjects::updateTuioObject,&InputGestureDirectObjects::updateTuioObject);
    registerEvent(InputGestureBasicObjects::removeTuioObject,&InputGestureDirectObjects::removeTuioObject);
    registerEvent(InputGestureBasicObjects::exitTuioObject,&InputGestureDirectObjects::exitTuioObject);
}

void InputGestureDirectObjects::addTuioObject(InputGestureBasicObjects::addTuioObjectArgs & a)
{
    DirectObject * dob = new DirectObject();
    dob->s_id = a.id;
    dob->f_id = a.f_id;
    dob->set(a.xpos, a.ypos);
    dob->orientation = a.angle;
    dob->xspeed = a.xspeed;
    dob->yspeed= a.yspeed;
    dob->rspeed = a.rspeed;
    dob->maccel = a.maccel;
    dob->raccel = a.raccel;
    objects[a.id]= dob;
    newObjectArgs eventargs;
    eventargs.object = dob;
    eventargs.target = a.target;
    ofNotifyEvent(newObject,eventargs);
}

void InputGestureDirectObjects::enterTuioObject(InputGestureBasicObjects::enterTuioObjectArgs & a)
{
    DirectObject * dob = objects[a.id];
    dob->s_id = a.id;
    dob->f_id = a.f_id;
    dob->set(a.xpos, a.ypos);
    dob->orientation = a.angle;
    dob->xspeed = a.xspeed;
    dob->yspeed= a.yspeed;
    dob->rspeed = a.rspeed;
    dob->maccel = a.maccel;
    dob->raccel = a.raccel;
    objects[a.id]= dob;
    enterObjectArgs eventargs;
    eventargs.object = dob;
    eventargs.target = a.target;
    ofNotifyEvent(enterObject,eventargs);

}

void InputGestureDirectObjects::updateTuioObject(InputGestureBasicObjects::updateTuioObjectArgs & a)
{
    DirectObject * dob = objects[a.id];
    dob->s_id = a.id;
    dob->f_id = a.f_id;
    dob->set(a.xpos, a.ypos);

    float increment = a.angle - dob->orientation;
    if (increment > PI){
        increment -= 2*PI;
    }else if (increment < -PI){
        increment += 2*PI;
    }

    dob->orientation = a.angle;
    dob->xspeed = a.xspeed;
    dob->yspeed= a.yspeed;
    dob->rspeed = a.rspeed;
    dob->maccel = a.maccel;
    dob->raccel = a.raccel;
    objects[a.id]= dob;
    updateObjectArgs eventargs;
    eventargs.object = dob;
    eventargs.target = a.target;
    ofNotifyEvent(updateObject,eventargs);

}

void InputGestureDirectObjects::removeTuioObject(InputGestureBasicObjects::removeTuioObjectArgs & a)
{
    removeObjectArgs eventargs;
    eventargs.object = objects[a.id];
    eventargs.target = a.target;
    ofNotifyEvent(removeObject,eventargs);

}

void InputGestureDirectObjects::exitTuioObject(InputGestureBasicObjects::exitTuioObjectArgs & a)
{
    exitObjectArgs eventargs;
    eventargs.object = objects[a.id];
    eventargs.target = a.target;
    ofNotifyEvent(exitObject,eventargs);

}

