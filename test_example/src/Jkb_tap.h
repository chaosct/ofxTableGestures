#ifndef JKB_TAP_H
#define JKB_TAP_H

#include "InputGesture.hpp"
#include "TEvent.hpp"
#include "tuioApp.hpp"
#include "DirectPoint.hpp"
#include "InputGestureBasicFingers.hpp"
#include <map>
#include "Jkb_finger.h"

namespace jkb_gesture{

    class TevenTap : public tuio::TTEvent<TevenTap>{
        public:
            float x,y;
    };

    class InputGestureTap : public tuio::CanBasicFingers < tuio::CompositeGesture >{
        std::map<int32,Timed_jkb_finger *> fingers;
        public:
            InputGestureTap(){}

            void addTuioCursor(int32 id, float xpos,float ypos,float xspeed,float yspeed,float maccel){
                Timed_jkb_finger * e = new Timed_jkb_finger();
                e->s_id = id;
                e->AddPoint(xpos,ypos);
                fingers[id]=e;
            }

            void updateTuioCursor(int32 id, float xpos,float ypos,float xspeed,float yspeed,float maccel){
                Timed_jkb_finger * e = fingers[id];
                e->AddPoint(xpos,ypos);
            }

            void removeTuioCursor(int32 id){
/*                TevenRemoveTimedFinger * evt = new TevenRemoveTimedFinger();
                evt->finger = fingers[id];
                events.push_back(evt);
                //fingers.erase(id);*/
            }
        };

        template <class Base>
        class CanTap : public  Base
        {
            public:
            //Interface redefined by ofApp
            virtual void Tap(float x, float y){}

            //processing events callbacks
            TEventHandler(TevenTap)
            {
                TevenTap * e = static_cast<TevenTap *>(evt);
                Tap(e->x,e->y);
            }
            //registering
            CanTap()
            {
                TRegistraCallback(CanTap,TevenTap);
                Base::registerInputGesture(Singleton<InputGestureTap>::get());
            }

        };
}

#endif // JKB_TAP_H
