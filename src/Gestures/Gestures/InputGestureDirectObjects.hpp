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

#ifndef INPUTGESTUREDIRECTOBJECTS_H_INCLUDED
#define INPUTGESTUREDIRECTOBJECTS_H_INCLUDED

#include "InputGestureBasicObjects.hpp"
#include <map>

class DirectObject : public ofVec2f{
public:
    DirectObject(int _s_id, int _f_id,
                float _xpos, float _ypos, float _angle,
                float _xspeed, float _yspeed, float _rspeed,
                float _maccel, float _raccel) :
        ofVec2f(_xpos, _ypos), s_id(_s_id), f_id(_f_id),
        orientation(_angle),
        xspeed(_xspeed), yspeed(_yspeed), rspeed(_rspeed),
        maccel(_maccel), raccel(_raccel) {}

    DirectObject() : ofVec2f(0),
	s_id(-1), f_id(0),
        orientation(0),
        xspeed(0), yspeed(0), rspeed(0),
        maccel(0), raccel(0) {}

    DirectObject(const DirectObject& rhs) : ofVec2f(rhs),
	s_id(rhs.s_id), f_id(rhs.f_id),
        orientation(rhs.orientation),
        xspeed(rhs.xspeed), yspeed(rhs.yspeed), rspeed(rhs.rspeed),
        maccel(rhs.maccel), raccel(rhs.raccel) {}

    int s_id, f_id;
    float orientation, xspeed, yspeed, rspeed, maccel, raccel;
};



class InputGestureDirectObjects : public EventClient{
        struct DirectObjectArgsBase : public EventArgs{
            DirectObject * object;
        };
        std::map<int,DirectObject *> objects;

    public:
        typedef DirectObjectArgsBase newObjectArgs;
        typedef DirectObjectArgsBase removeObjectArgs;
        typedef DirectObjectArgsBase updateObjectArgs;
        typedef DirectObjectArgsBase enterObjectArgs;
        typedef DirectObjectArgsBase exitObjectArgs;

        static ofEvent<newObjectArgs> newObject;
        static ofEvent<removeObjectArgs> removeObject;
        static ofEvent<updateObjectArgs> updateObject;
        static ofEvent<enterObjectArgs> enterObject;
        static ofEvent<exitObjectArgs> exitObject;

        InputGestureDirectObjects();
        void addTuioObject(InputGestureBasicObjects::addTuioObjectArgs & a);
        void enterTuioObject(InputGestureBasicObjects::enterTuioObjectArgs & a);
        void updateTuioObject(InputGestureBasicObjects::updateTuioObjectArgs & a);
        void removeTuioObject(InputGestureBasicObjects::removeTuioObjectArgs & a);
        void exitTuioObject(InputGestureBasicObjects::exitTuioObjectArgs & a);
};

template <class Base>
class CanDirectObjects : public Base{
    public:
        void EnewObject(InputGestureDirectObjects::newObjectArgs & eventargs){
            newObject(eventargs.object);
        }
        virtual void newObject(DirectObject*) {}
        void EremoveObject(InputGestureDirectObjects::removeObjectArgs & eventargs){
            removeObject(eventargs.object);
        }
        virtual void removeObject(DirectObject*) {}
        void EupdateObject(InputGestureDirectObjects::updateObjectArgs & eventargs){
            updateObject(eventargs.object);
        }
        virtual void updateObject(DirectObject*) {}
        void EenterObject(InputGestureDirectObjects::enterObjectArgs & eventargs){
            enterObject(eventargs.object);
        }
        virtual void enterObject(DirectObject* object){
            newObject(object);
        }
        void EexitObject(InputGestureDirectObjects::exitObjectArgs & eventargs){
            exitObject(eventargs.object);
        }
        virtual void exitObject(DirectObject* object){
            removeObject(object);
        }

        //registering
        CanDirectObjects(){
            ofAddListener(InputGestureDirectObjects::newObject,this,&CanDirectObjects::EnewObject);
            ofAddListener(InputGestureDirectObjects::removeObject,this,&CanDirectObjects::EremoveObject);
            ofAddListener(InputGestureDirectObjects::updateObject,this,&CanDirectObjects::EupdateObject);
            ofAddListener(InputGestureDirectObjects::enterObject,this,&CanDirectObjects::EenterObject);
            ofAddListener(InputGestureDirectObjects::exitObject,this,&CanDirectObjects::EexitObject);
        }

        virtual ~CanDirectObjects(){
            ofRemoveListener(InputGestureDirectObjects::newObject,this,&CanDirectObjects::EnewObject);
            ofRemoveListener(InputGestureDirectObjects::removeObject,this,&CanDirectObjects::EremoveObject);
            ofRemoveListener(InputGestureDirectObjects::updateObject,this,&CanDirectObjects::EupdateObject);
            ofRemoveListener(InputGestureDirectObjects::enterObject,this,&CanDirectObjects::EenterObject);
            ofRemoveListener(InputGestureDirectObjects::exitObject,this,&CanDirectObjects::EexitObject);
        }
};

#endif // INPUTGESTUREDIRECTOBJECTS_H_INCLUDED

