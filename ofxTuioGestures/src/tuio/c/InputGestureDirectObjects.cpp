#include "InputGestureDirectObjects.h"

namespace tuio
{

void InputGestureDirectObjects::addTuioObject(int32 id, int32 f_id ,float xpos,float ypos, float angle, float xspeed,float yspeed,float rspeed,float maccel, float raccel)
{
    DirectObject * dob = new DirectObject();
    dob->s_id = id;
    dob->f_id = f_id;
    dob->xpos= xpos;
    dob->ypos = ypos;
    dob->angle = angle;
    dob->xspeed = xspeed;
    dob->yspeed= yspeed;
    dob->rspeed = rspeed;
    dob->maccel = maccel;
    dob->raccel = raccel;
    objects[id]= dob;
    TeventDirectObjectsNewObject * evt = new TeventDirectObjectsNewObject();
    evt->dob = dob;
    evt->f_id = f_id;
    evt->s_id = id;
    events.push_back(evt);

}
void InputGestureDirectObjects::updateTuioObject(int32 id, int32 f_id ,float xpos,float ypos, float angle, float xspeed,float yspeed,float rspeed,float maccel, float raccel)
{
    DirectObject * dob = objects[id];
    dob->s_id = id;
    dob->f_id = f_id;
    dob->xpos= xpos;
    dob->ypos = ypos;
    dob->angle = angle;
    dob->xspeed = xspeed;
    dob->yspeed= yspeed;
    dob->rspeed = rspeed;
    dob->maccel = maccel;
    dob->raccel = raccel;

}
void InputGestureDirectObjects::removeTuioObject(int32 id)
{
    TeventDirectObjectsRemoveObject * evt = new TeventDirectObjectsRemoveObject();
    evt->s_id = id;
    evt->f_id = objects[id]->f_id;
    events.push_back(evt);

}
}
