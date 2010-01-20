#ifndef INPUTLISTENER_H_INCLUDED
#define INPUTLISTENER_H_INCLUDED

#include "tuioApp.h"
#include "Dispatcher.h"

namespace tuio
{
    class Dispatcher;

    ///Listener -> This class is attached automatically to "Dispatcher" and detached at destuction
    /// it is the base class for all capabilities that will be used.
    class Listener{
        ///eventprocessors -> map of all event processors capabilities added to Listener
        eventprocessorsType eventprocessors;
        public:
            ///Listener()
            ///inputs: none
            ///constructor attaches automatically itself to Dispatcher
            Listener();
            ///virtual ~Listener()=0;
            ///destructor detaches itself from Dispatcher
            virtual ~Listener()=0;
            ///void processTevent(TEvent * te)
            ///outputs: none
            ///inputs:
            ///     TEvent * te -> the event to be processed
            ///Desc: Processes the event (or not, it checks the if the event processor exists before)
            virtual void processTevent(TEvent * te);
            ///eventprocessorsType & getEP()
            ///outputs:
            ///     eventprocessorsType ->
            ///Needed for adding new capabilities.
            eventprocessorsType & getEP();
    };
}

#endif // INPUTLISTENER_H_INCLUDED
