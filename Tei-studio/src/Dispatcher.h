#ifndef DISPATCHER_H_INCLUDED
#define DISPATCHER_H_INCLUDED

#include "tuioApp.h"
#include "InputListener.h"

namespace tuio
{
    class Listener;

    class Dispatcher{
        private:
            std::list<Listener*> listeners_list;
        public:
            static Dispatcher& Instance(){
                return Singleton<Dispatcher>::Instance();
            }
            EventQueue * equeue;
            Dispatcher(){
                Singleton<tuio::tuioinput>::Instance().init();
                equeue = Singleton<tuio::tuioinput>::Instance().getQueue();
            }
            //std::list<tuioApp*> apps;
            void AddListener(Listener* listener){
                listeners_list.push_back(listener);
            }
            void RemoveListener(Listener* listener){
                listeners_list.remove(listener);
            }
            void processTevents();
            void tostring();

    };
}

#endif // DISPATCHER_H_INCLUDED
