/*

    OF-TangibleFramework . Framework for Tei-studio
    Universitat Pompeu Fabra

    Copyright (c) 2009 Daniel Gallardo Grassot <daniel.gallardo@upf.edu>

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

#include "InputGestureObjectFinger.h"

using namespace tuio;

/**
* OBJECTFINGER METHODS
**/
objectfinger::objectfinger(DirectObject* obj):object(obj){
}

float objectfinger::distance (DirectFinger* finger){
    return object->getDistance(*finger);
}

float objectfinger::distance (float x, float y){
    return object->getDistance(x,y);
}

void objectfinger::fingerAdd(DirectFinger* finger){
    fingers[finger->s_id] = finger;
}

void objectfinger::fingerRemove(int32 s_id){
    fingers.erase(s_id);
}

bool objectfinger::containsFinger(int32 id){
    std::map<int32, DirectFinger*>::iterator it = fingers.find(id);
    if(it != fingers.end())return true;
    return false;
}
/**
* END OBJECTFINGER METHODS
**/

/**
* INPUTOBJECTFINGER METHODS
**/
InputObjectFinger::InputObjectFinger(){
}


void InputObjectFinger::newObject(int32 s_id, int32 f_id, DirectObject * obj){
    /// add the object to tne map
    objects[s_id]= new objectfinger(obj);
}

void InputObjectFinger::removeObject(int32 s_id, int32 f_id){
    ///recuperate the object data
    objectfinger* obfi = objects[s_id];
    ///erases this data (map)
    objects.erase(s_id);
    ///foreach finger related with the removeved object
    for (std::map<int32, DirectFinger*>::iterator it = obfi->fingers.begin(); it != obfi->fingers.end(); it++){
        ///add it to the orphan list
        orphan_fingers[it->first] = it->second;
        /// creates the event object finger removed
        TeventObjectFingerRelease * evt = new TeventObjectFingerRelease();
        evt->object = obfi->object;
        evt->finger = it->second;
        events.push_back(evt);
        /// end object finger removed
    }
    ///deletes the object instance
    delete obfi;
}

void InputObjectFinger::newCursor(int32 id, DirectFinger * dfi){
    ///sets initial object vars to impossible values for
    ///searching the correct ones
    objectfinger* tmp = NULL;
    float distance = 99;
    ///foreach stored object
    for(std::map<int32,objectfinger*>::iterator it = objects.begin(); it != objects.end(); it++ ){
        float tmp_dist = it->second->distance(dfi);
        ///checks if the distance is less than the anterior
        if (tmp_dist < distance){
            ///if it is true, the object is pointed
            distance = tmp_dist;
            tmp = it->second;
        }
    }
    ///if distance is less than Gesturedistance
    if(distance <= GESTURE_DISTANCE && tmp != NULL){
        ///adds the finger to the gesture
        tmp->fingerAdd(dfi);
        /// generates the event object fingeradd
        TeventObjectFingerAdd * evt = new TeventObjectFingerAdd();
        evt->object = tmp->object;
        evt->finger = dfi;
        events.push_back(evt);
        /// end of event object fingeradd
    }else{
        ///if conditions are not acomplished stores the point into orphan list
        orphan_fingers[dfi->s_id]=dfi;
    }
}

void InputObjectFinger::removeCursor(int32 id){
    bool found = false;
    ///foreach object
    for(std::map<int32,objectfinger*>::iterator it = objects.begin(); it != objects.end(); it++ ){
        ///check if it contains the cursor to be removed
        if(it->second->containsFinger(id)){
            /// generates an event object finger removed
            TeventObjectFingerRelease * evt = new TeventObjectFingerRelease();
            evt->object = it->second->object;
            evt->finger = it->second->fingers[id];
            events.push_back(evt);
            /// end event object finger removed
            ///removes the finger
            it->second->fingerRemove(id);
            found = true;
        }
    }
    ///if it wasn't related with an object
    if(!found){
        ///check and delete the orphan finger
        std::map<int32,DirectFinger*>::iterator it = orphan_fingers.find(id);
        if (it != orphan_fingers.end()){
            orphan_fingers.erase(id);
        }else{
            ///This means that an unexistent finger have been removed :S
            std::cout << "objectfinger: unexpected error erasing finger" << std::endl;
        }
    }
}

void InputObjectFinger::updateTuioCursor(int32 id, float xpos,float ypos,float xspeed,float yspeed,float maccel){
    bool found = false;
    ///foreach object
    for(std::map<int32,objectfinger*>::iterator it = objects.begin(); it != objects.end(); it++ ){
        ///check if it contains the cursor to be removed
        if(it->second->containsFinger(id)){
            /// generates an event object finger updated
            TeventObjectFingerUpdate * evt = new TeventObjectFingerUpdate();
            evt->object = it->second->object;
            evt->finger = it->second->fingers[id];
            events.push_back(evt);
            /// end event object finger updated
            found = true;
        }
    }
    ///if it wasn't related with an object
    if(!found){
        ///finds the orphan finger
        std::map<int32,DirectFinger*>::iterator it = orphan_fingers.find(id);
        if (it != orphan_fingers.end()){
            DirectFinger * finger = it->second;
            ///removes the orphan finger
            orphan_fingers.erase(id);
            /// tries to link it with an object
            newCursor(finger->s_id, finger);
        }else{
            ///This means that an unexistent finger have been updated :S
            std::cout << "objectfinger: unexpected error updating finger" << std::endl;
        }
    }
}

void InputObjectFinger::tap(float x, float y) {
    objectfinger* found = NULL;
    float distance = 99;
    ///foreach object, search the nearest to the tap
    for(std::map<int32,objectfinger*>::iterator it = objects.begin(); it != objects.end(); it++ ){
        float tmp_distance = it->second->distance(x,y);
        if(tmp_distance <= distance){
            distance = tmp_distance;
            found = it->second;
        }
    }
    /// checks if the distance is apropiate for considerating it as a gesture
    if (distance <= GESTURE_DISTANCE && found != NULL){
        /// generates event object finger tab
        TeventObjectFingerTap * evt = new TeventObjectFingerTap();
        evt->object = found->object;
        evt->x = x;
        evt->y = y;
        events.push_back(evt);
        /// end event object finger tab
    }
}
/**
* END INPUTOBJECTFINGER METHODS
**/
