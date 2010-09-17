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

namespace tuio
{

void InputGestureDirectObjects::addTuioObject(int32 id, int32 f_id ,float xpos,float ypos, float angle, float xspeed,float yspeed,float rspeed,float maccel, float raccel)
{
    DirectObject * dob = new DirectObject();
    dob->s_id = id;
    dob->f_id = f_id;
    dob->setX( xpos);
    dob->setY( ypos);
    dob->angle = angle;
    dob->xspeed = xspeed;
    dob->yspeed= yspeed;
    dob->rspeed = rspeed;
    dob->maccel = maccel;
    dob->raccel = raccel;
    objects[id]= dob;
    SimpleCallEvent(CanDirectObjects,newObject,(dob));
}

void InputGestureDirectObjects::enterTuioObject(int32 id, int32 f_id ,float xpos,float ypos, float angle, float xspeed,float yspeed,float rspeed,float maccel, float raccel)
{
    DirectObject * dob = new DirectObject();
    dob->s_id = id;
    dob->f_id = f_id;
    dob->setX( xpos);
    dob->setY( ypos);
    dob->angle = angle;
    dob->xspeed = xspeed;
    dob->yspeed= yspeed;
    dob->rspeed = rspeed;
    dob->maccel = maccel;
    dob->raccel = raccel;
    objects[id]= dob;
    SimpleCallEvent(CanDirectObjects,enterObject,(dob));
}

void InputGestureDirectObjects::updateTuioObject(int32 id, int32 f_id ,float xpos,float ypos, float angle, float xspeed,float yspeed,float rspeed,float maccel, float raccel)
{
    DirectObject * dob = objects[id];
    dob->s_id = id;
    dob->f_id = f_id;
    dob->setX( xpos);
    dob->setY( ypos);
    dob->angle = angle;
    dob->xspeed = xspeed;
    dob->yspeed= yspeed;
    dob->rspeed = rspeed;
    dob->maccel = maccel;
    dob->raccel = raccel;
    SimpleCallEvent(CanDirectObjects,updateObject,(dob));
}

void InputGestureDirectObjects::removeTuioObject(int32 id)
{
    SimpleCallEvent(CanDirectObjects,removeObject,(objects[id]));
}

void InputGestureDirectObjects::exitTuioObject(int32 id)
{
    SimpleCallEvent(CanDirectObjects,exitObject,(objects[id]));
}

}
