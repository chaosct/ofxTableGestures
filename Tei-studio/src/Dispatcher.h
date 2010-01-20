#ifndef DISPATCHER_H_INCLUDED
#define DISPATCHER_H_INCLUDED

#include "tuioApp.h"
#include "InputListener.h"

namespace tuio
{
    class Listener;

    ///This class stores an instance of all Listenenrs and distribute the generated events
    class Dispatcher{
        private:
            ///List where all Listeners will be stored
            std::list<Listener*> listeners_list;
            ///queue of generated events
            EventQueue * equeue;
        public:
            ///Dispatcher()
            ///Constructor, it starts the tuioinput thread (if not started) and recuperates the eventqueue
            Dispatcher(){
                Singleton<tuio::tuioinput>::Instance().init();
                equeue = Singleton<tuio::tuioinput>::Instance().getQueue();
            }
            ///static Dispatcher& Instance()
            ///outputs:
            ///     Dispatcher& -> a unique instance of a Dispatcher
            ///inputs: none
            ///Desc: Singleton access to dispatcher
            static Dispatcher& Instance(){
                return Singleton<Dispatcher>::Instance();
            }
            ///void AddListener(Listener* listener)
            ///outputs:none
            ///inputs:
            ///     Listener* listener -> pointer to a listener.
            ///Desc: Adds a listener to listeners_list
            void AddListener(Listener* listener){
                listeners_list.push_back(listener);
            }
            ///void RemoveListener(Listener* listener)
            ///outputs:none
            ///inputs:
            ///     Listener* listener -> pointer to a listener.
            ///Desc: Removes a Listener from listeners_list
            void RemoveListener(Listener* listener){
                listeners_list.remove(listener);
            }
            ///void processTevents();
            ///outputs: none
            ///inputs: none
            ///Desc: foreach event stored into the eventqueue executes the
            ///process event of each Listener stored into listeners_list
            void processTevents();
            ///void tostring();
            ///outputs: none
            ///inputs: none
            ///Desc: shows at stdoutput the number of listeners added
            void tostring();

    };
}

#endif // DISPATCHER_H_INCLUDED
