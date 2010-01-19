#ifndef INPUTGESTUREFINGEROBJECT_H_INCLUDED
#define INPUTGESTUREFINGEROBJECT_H_INCLUDED

#include "InputGestureDummyClick.h"
#include "InputGestureDirectFingers.h"
#include "InputGestureBasicFingers.h"
#include "InputGestureDirectObjects.h"
#include "TEvent.h"
#include <map>
#include <list>

///Physical radius of an average fiducial size
#define FIGURE_OFFSET       0.035f
///gesture bound
#define GESTURE_DISTANCE    FIGURE_OFFSET+0.05f

namespace tuio
{

class objectfinger
{
    public:
    /// stores data of the object
    DirectObject* object;
    /// stores finger data related with the object
    std::map<int32, DirectFinger*> fingers;

    ///constructor
    objectfinger(DirectObject* obj):object(obj){}
    ///distance object-finger
    float distance (DirectFinger* finger){
        return object->getDistance(*finger);
    }
    ///relates finger with the object
    void fingerAdd(DirectFinger* finger){
        fingers[finger->s_id] = finger;
    }
    ///removes finger
    void fingerRemove(int32 s_id){
        fingers.erase(s_id);
    }
    ///check if finger is related
    bool containsFinger(int32 id){
        std::map<int32, DirectFinger*>::iterator it = fingers.find(id);
        if(it != fingers.end())return true;
        return false;
    }
};

/// Events declare
/// TeventObjectFingerAdd -> reports an adition of a finger
class TeventObjectFingerAdd : public TTEvent <TeventObjectFingerAdd>
{
public:
    DirectObject* object;
    DirectFinger* finger;
};
/// TeventObjectFingerUpdate -> reports an update of a finger
class TeventObjectFingerUpdate : public TTEvent <TeventObjectFingerUpdate>
{
public:
    DirectObject* object;
    DirectFinger* finger;
};
/// TeventObjectFingerRelease -> reports a release of a finger
class TeventObjectFingerRelease : public TTEvent <TeventObjectFingerRelease>
{
public:
    DirectObject* object;
    DirectFinger* finger;
};
/*/// TeventObjectFingerTap -> reports a 'Tap' gesture of a finger
class TeventObjectFingerTap : public TTEvent <TeventObjectFingerTap>
{
public:
    DirectObject* object;
    DirectFinger* finger;
};*/

class InputObjectFinger : public CanBasicFingers < CanDirectFingers < CanDirectObjects < tuioApp <InputGesture> > > >
{
    private:
        std::map<int32,objectfinger*> objects;
        std::map<int32,DirectFinger*> orphan_fingers;
        InputGestureBasicFingers * basicfingers;
        InputGestureDirectFingers * directfingers;
        InputGestureDirectObjects * directobjects;
    public:
        InputObjectFinger(){
            basicfingers = Singleton < InputGestureBasicFingers >::get();
            directfingers = Singleton < InputGestureDirectFingers >::get();
            directobjects = Singleton < InputGestureDirectObjects >::get();
        }
        virtual void ReceiveCall(const char * addr, osc::ReceivedMessageArgumentStream & argList)
        {
            for (std::list<TEvent *>::iterator it = basicfingers->events.begin() ; it != basicfingers->events.end() ; ++it)
                processTevent(*it);
            for (std::list<TEvent *>::iterator it = directfingers->events.begin() ; it != directfingers->events.end() ; ++it)
                processTevent(*it);
            for (std::list<TEvent *>::iterator it = directobjects->events.begin() ; it != directobjects->events.end() ; ++it)
                processTevent(*it);
        }
        ///FromCanDirectObjects
        virtual void newObject(int32 s_id, int32 f_id, DirectObject * obj){
            objects[s_id]= new objectfinger(obj);
        }
        virtual void removeObject(int32 s_id, int32 f_id){
            objectfinger* obfi = objects[s_id];
            objects.erase(s_id);
            for (std::map<int32, DirectFinger*>::iterator it = obfi->fingers.begin(); it != obfi->fingers.end(); it++){
                orphan_fingers[it->first] = it->second;
                /// event object finger removed
                TeventObjectFingerRelease * evt = new TeventObjectFingerRelease();
                evt->object = obfi->object;
                evt->finger = it->second;
                events.push_back(evt);
                /// event object finger removed
            }
            delete obfi;
        }
        ///FromCanDirectFingers
        virtual void newCursor(int32 id, DirectFinger * dfi){
            objectfinger* tmp = NULL;
            float distance = 99;
            for(std::map<int32,objectfinger*>::iterator it = objects.begin(); it != objects.end(); it++ ){
                float tmp_dist = it->second->distance(dfi);
                if (tmp_dist < distance){
                    distance = tmp_dist;
                    tmp = it->second;
                }
            }
            if(distance <= GESTURE_DISTANCE){
                tmp->fingerAdd(dfi);
                /// crear event object fingeradd
                TeventObjectFingerAdd * evt = new TeventObjectFingerAdd();
                evt->object = tmp->object;
                evt->finger = dfi;
                events.push_back(evt);
                /// crear event object fingeradd
            }else{
                orphan_fingers[dfi->s_id]=dfi;
            }

        }
        virtual void removeCursor(int32 id){
            bool found = false;
            for(std::map<int32,objectfinger*>::iterator it = objects.begin(); it != objects.end(); it++ ){
                if(it->second->containsFinger(id)){
                    /// event object finger removed
                    TeventObjectFingerRelease * evt = new TeventObjectFingerRelease();
                    evt->object = it->second->object;
                    evt->finger = it->second->fingers[id];
                    events.push_back(evt);
                    /// event object finger removed
                    it->second->fingerRemove(id);
                    found = true;
                }
            }
            if(!found){
                std::map<int32,DirectFinger*>::iterator it = orphan_fingers.find(id);
                if (it != orphan_fingers.end()){
                    orphan_fingers.erase(id);
                }else{
                    std::cout << "objectfinger: unexpected error erasing finger" << std::endl;
                }
            }
        }
        /// from can basic fingers
        virtual void updateTuioCursor(int32 id, float xpos,float ypos,float xspeed,float yspeed,float maccel){
            bool found = false;
            for(std::map<int32,objectfinger*>::iterator it = objects.begin(); it != objects.end(); it++ ){
                if(it->second->containsFinger(id)){
                    /// crear event object finger updated
                    TeventObjectFingerUpdate * evt = new TeventObjectFingerUpdate();
                    evt->object = it->second->object;
                    evt->finger = it->second->fingers[id];
                    events.push_back(evt);
                    /// crear event object finger updated
                    found = true;
                }
            }
            if(!found){
                std::map<int32,DirectFinger*>::iterator it = orphan_fingers.find(id);
                if (it != orphan_fingers.end()){
                    newCursor(id, it->second);
                }else{
                    std::cout << "objectfinger: unexpected error updating finger" << std::endl;
                }
            }
        }
};

template <class Base>
class CanObjectFinger : public  Base
{
public:
    //Interface redefined by ofApp
    virtual void objectFingerAdd(DirectObject* obj, DirectFinger* finger) {}
    virtual void objectFingerUpdate(DirectObject* obj, DirectFinger* finger) {}
    virtual void objectFingerRemove(DirectObject* obj, DirectFinger* finger) {}

    //processing events callbacks
    TEventHandler(TeventObjectFingerAdd)
    {
        TeventObjectFingerAdd * e = static_cast<TeventObjectFingerAdd *>(evt);
        objectFingerAdd(e->object,e->finger);
    }
    TEventHandler(TeventObjectFingerUpdate)
    {
        TeventObjectFingerUpdate * e = static_cast<TeventObjectFingerUpdate *>(evt);
        objectFingerUpdate(e->object,e->finger);
    }
    TEventHandler(TeventObjectFingerRelease)
    {
        TeventObjectFingerRelease * e = static_cast<TeventObjectFingerRelease *>(evt);
        objectFingerRemove(e->object,e->finger);
    }

    //registering
    CanObjectFinger()
    {
        TRegistraCallback(CanObjectFinger,TeventObjectFingerAdd);
        TRegistraCallback(CanObjectFinger,TeventObjectFingerUpdate);
        TRegistraCallback(CanObjectFinger,TeventObjectFingerRelease);
        registerMeToInputGestureManager(Singleton<InputObjectFinger>::get());
    }

    //allways needed
    eventprocessorsType & getEP()
    {
        return Base::getEP();
    }
};

}

#endif // INPUTGESTUREFINGEROBJECT_H_INCLUDED
