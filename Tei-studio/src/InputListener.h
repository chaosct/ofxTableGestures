#ifndef INPUTLISTENER_H_INCLUDED
#define INPUTLISTENER_H_INCLUDED

#include "tuioApp.h"
#include "Dispatcher.h"

namespace tuio
{
    class Dispatcher;

    ///Listener -> This class is attached automatically to "Dispatcher" and detached at destuction
    /// it is the base class for all capabilities that will be used.
    class Listener : public tuioAppBase
    {
        public:
            ///Listener()
            ///inputs: none
            ///constructor attaches automatically itself to Dispatcher
            Listener();
            ///virtual ~Listener()=0;
            ///destructor detaches itself from Dispatcher
            virtual ~Listener()=0;
    };
}

#endif // INPUTLISTENER_H_INCLUDED
