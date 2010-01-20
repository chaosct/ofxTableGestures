#ifndef INPUTLISTENER_H_INCLUDED
#define INPUTLISTENER_H_INCLUDED

#include "tuioApp.h"
#include "Dispatcher.h"

namespace tuio
{
    class Dispatcher;

    class Listener{
        eventprocessorsType eventprocessors;
        public:
            Listener();
            virtual void processTevent(TEvent * te);
            eventprocessorsType & getEP();
    };
}

#endif // INPUTLISTENER_H_INCLUDED
