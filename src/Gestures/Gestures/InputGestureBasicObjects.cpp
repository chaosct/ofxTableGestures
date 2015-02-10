#include "InputGestureBasicObjects.hpp"
#include "GenericManager.hpp"
#include "GraphicDispatcher.hpp"

ofEvent<InputGestureBasicObjects::removeTuioObjectArgs> InputGestureBasicObjects::removeTuioObject;
ofEvent<InputGestureBasicObjects::exitTuioObjectArgs> InputGestureBasicObjects::exitTuioObject;
ofEvent<InputGestureBasicObjects::addTuioObjectArgs> InputGestureBasicObjects::addTuioObject;
ofEvent<InputGestureBasicObjects::enterTuioObjectArgs> InputGestureBasicObjects::enterTuioObject;
ofEvent<InputGestureBasicObjects::updateTuioObjectArgs> InputGestureBasicObjects::updateTuioObject;

InputGestureBasicObjects::InputGestureBasicObjects()
{
    registerEvent( InputGestureTuio112D::removeTuioObject2D , &InputGestureBasicObjects::removeTuioObject2D );
    registerEvent( InputGestureTuio112D::updateTuioObject2D , &InputGestureBasicObjects::updateTuioObject2D );
    registerEvent( InputGestureTuio112D::addTuioObject2D , &InputGestureBasicObjects::addTuioObject2D );
}

void InputGestureBasicObjects::addTuioObject2D(int id, int f_id ,float xpos,float ypos, float angle, float xspeed,float yspeed,float rspeed,float maccel, float raccel)
{

        ids.insert(id);
        const Graphic * target = GenericManager::get<GraphicDispatcher>()->Collide(ofPoint(xpos,ypos));
        graphic_assignations[id] = target;
        addTuioObjectArgs eventargs;
        eventargs.id = id;
        eventargs.f_id = f_id ;
        eventargs.xpos = xpos;
        eventargs.ypos = ypos;
        eventargs.angle = angle;
        eventargs.xspeed = xspeed;
        eventargs.yspeed = yspeed;
        eventargs.rspeed = rspeed;
        eventargs.maccel = maccel;
        eventargs.raccel = raccel;
        eventargs.target = target;
        ofNotifyEvent(addTuioObject,eventargs);

}

void InputGestureBasicObjects::updateTuioObject2D(int id, int f_id ,float xpos,float ypos, float angle, float xspeed,float yspeed,float rspeed,float maccel, float raccel)
{

    if(ids.find(id) == ids.end())
    {
        addTuioObject2D(id,f_id,xpos,ypos,angle,xspeed,yspeed,rspeed,maccel,raccel);
        return;
    }

    const Graphic * target = GenericManager::get<GraphicDispatcher>()->Collide(ofPoint(xpos,ypos));

    if(graphic_assignations[id] != target)
    {
        {
            exitTuioObjectArgs eventargs;
            eventargs.id = id;
            eventargs.target = graphic_assignations[id];
            ofNotifyEvent(exitTuioObject,eventargs);
        }
        graphic_assignations[id] = target;
        {
            enterTuioObjectArgs eventargs;
            eventargs.id = id;
            eventargs.f_id = f_id;
            eventargs.xpos = xpos;
            eventargs.ypos = ypos;
            eventargs.angle = angle;
            eventargs.xspeed = xspeed;
            eventargs.yspeed = yspeed;
            eventargs.rspeed = rspeed;
            eventargs.maccel = maccel;
            eventargs.raccel = raccel;
            eventargs.target = target;
            ofNotifyEvent(enterTuioObject,eventargs);
        }
    }

    updateTuioObjectArgs eventargs;
    eventargs.id = id;
    eventargs.f_id = f_id;
    eventargs.xpos = xpos;
    eventargs.ypos = ypos;
    eventargs.angle = angle;
    eventargs.xspeed = xspeed;
    eventargs.yspeed = yspeed;
    eventargs.rspeed = rspeed;
    eventargs.maccel = maccel;
    eventargs.raccel = raccel;
    eventargs.target = target;
    ofNotifyEvent(updateTuioObject,eventargs);

}

void InputGestureBasicObjects::removeTuioObject2D(int id)
{
    if(ids.find(id) != ids.end())
    {
        ids.erase(id);
        removeTuioObjectArgs eventargs;
        eventargs.id = id;
        eventargs.target = graphic_assignations[id];
        ofNotifyEvent(removeTuioObject,eventargs);
        graphic_assignations.erase(id);

    }
}
