#ifndef JKB_FINGER_H
#define JKB_FINGER_H

#include "DirectPoint.hpp"
#include <list>
#include "ofMain.h"

#include "InputGesture.hpp"
#include "TEvent.hpp"
#include "tuioApp.hpp"
#include "InputGestureBasicFingers.hpp"
#include <map>

namespace jkb_gesture
{

    class Time_point{
        public:
        float time;
        DirectPoint point;
        Time_point(float _time, DirectPoint p):time(_time),point(p){}
    };

    typedef std::list<Time_point> time_points;

    class Timed_jkb_finger: public DirectPoint
    {
        public:
            time_points points;
            int32 s_id;
            void AddPoint(float x, float y){
                this->xpos = x;
                this->ypos = y;
                points.push_back( Time_point( ofGetElapsedTimef(), DirectPoint(*this) ) );
            }
    };

    class TevenAddTimedFinger : public tuio::TTEvent<TevenAddTimedFinger>{
        public:
            Timed_jkb_finger* finger;
    };

    class TevenUpdateTimedFinger : public tuio::TTEvent<TevenUpdateTimedFinger>{
        public:
            Timed_jkb_finger* finger;
    };

    class TevenRemoveTimedFinger : public tuio::TTEvent<TevenRemoveTimedFinger>{
        public:
            Timed_jkb_finger* finger;
    };

    class InputGestureTimedFingers : public tuio::CanBasicFingers < tuio::CompositeGesture >{
        std::map<int32,Timed_jkb_finger *> fingers;
        public:
            InputGestureTimedFingers(){}

            void addTuioCursor(int32 id, float xpos,float ypos,float xspeed,float yspeed,float maccel){
                Timed_jkb_finger * e = new Timed_jkb_finger();
                e->s_id = id;
                e->AddPoint(xpos,ypos);
                fingers[id]=e;

                TevenAddTimedFinger * evt = new TevenAddTimedFinger();
                evt->finger = e;
                events.push_back(evt);
            }

            void updateTuioCursor(int32 id, float xpos,float ypos,float xspeed,float yspeed,float maccel){
                Timed_jkb_finger * e = fingers[id];
                e->AddPoint(xpos,ypos);
                TevenUpdateTimedFinger * evt = new TevenUpdateTimedFinger();
                evt->finger = e;
                events.push_back(evt);
            }

            void removeTuioCursor(int32 id){
                TevenRemoveTimedFinger * evt = new TevenRemoveTimedFinger();
                evt->finger = fingers[id];
                events.push_back(evt);
                //fingers.erase(id);
            }
        };

        template <class Base>
        class CanTimedFingers : public  Base
        {
            public:
            //Interface redefined by ofApp
            virtual void newFinger(Timed_jkb_finger * finger){}
            virtual void updateFinger(Timed_jkb_finger * finger);
            virtual void removeFinger(Timed_jkb_finger * finger){}

            //processing events callbacks
            TEventHandler(TevenAddTimedFinger)
            {
                TevenAddTimedFinger * e = static_cast<TevenAddTimedFinger *>(evt);
                removeFinger(e->finger);
            }

            TEventHandler(TevenUpdateTimedFinger)
            {
                TevenUpdateTimedFinger * e = static_cast<TevenUpdateTimedFinger *>(evt);
                newFinger(e->finger);
            }

            TEventHandler(TevenRemoveTimedFinger)
            {
                TevenRemoveTimedFinger * e = static_cast<TevenRemoveTimedFinger *>(evt);
                removeFinger(e->finger);
            }

            //registering
            CanTimedFingers()
            {
                TRegistraCallback(CanTimedFingers,TevenAddTimedFinger);
                TRegistraCallback(CanTimedFingers,TevenUpdateTimedFinger);
                TRegistraCallback(CanTimedFingers,TevenRemoveTimedFinger);
                Base::registerInputGesture(Singleton<InputGestureTimedFingers>::get());
            }

        };
}

#endif // JKB_FINGER_H
