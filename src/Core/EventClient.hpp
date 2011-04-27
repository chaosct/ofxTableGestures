/*

    ofxTableGestures (formerly OF-TangibleFramework)
    Developed for Taller de Sistemes Interactius I
    Universitat Pompeu Fabra

    Copyright (c) 2011 Carles F. Julià <carles.fernandez@upf.edu>

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

#ifndef EVENTCLIENT_HPP_INCLUDED
#define EVENTCLIENT_HPP_INCLUDED

/// interface AbstractUnregister
/// Basically it's a commander, that do something
/// when unregister() is called.
/// We only use this to store collections
/// of EventUnregister objects.

struct AbstractUnregister
{
    virtual void unregister() = 0;
    virtual bool isevent(void * ) = 0;
    virtual ~AbstractUnregister(){}
};

/// template class EventUnregister
/// When created it stores the event, listener and method
/// to register to it , and it does the registration.
/// When unregister() is called it does the corresponding
/// unregistering.

template <class EventType,typename ArgumentsType, class ListenerClass>
struct EventUnregister: public AbstractUnregister
{
    EventType & event;
    ListenerClass  * listener;
    void (ListenerClass::*listenerMethod)(ArgumentsType&);

    void unregister()
    {
        ofRemoveListener(event,listener,listenerMethod);
    }
    
    bool isevent(void * eventptr)
    {
        void * myeventptr = static_cast<void *>(&event);
        return (eventptr == myeventptr);
    }

    EventUnregister(EventType & _event,
                    ListenerClass  * _listener,
                    void (ListenerClass::*_listenerMethod)(ArgumentsType&))

                    :event(_event),
                     listener(_listener),
                     listenerMethod(_listenerMethod)
    {
        ofAddListener(event,listener,listenerMethod);
    }

};

/// function make_unregister
/// Helper function to create EventUnregister
/// without having to type template stuff
/// it's like std::make_pair

template <class EventType,typename ArgumentsType, class ListenerClass>
AbstractUnregister * make_unregister(EventType & event,ListenerClass  * listener,void (ListenerClass::*listenerMethod)(ArgumentsType&))
{
    return new EventUnregister<EventType,ArgumentsType,ListenerClass>(event,listener,listenerMethod);
}

/// class EventClientObject
/// If you want a class to be able to automatically unregister 
/// event listeners when destroyed, use this class through
/// composition. Use :
///     registerEvent( this , Event , &MyClass::method );

class EventClientObject
{
    typedef std::list<AbstractUnregister*> UnregisterListType;
    UnregisterListType unregisterlist;
    public:
    template <class EventType,typename ArgumentsType, class ListenerClass>
    void registerEvent(ListenerClass * listener,EventType & event, void (ListenerClass::*listenerMethod)(ArgumentsType&))
    {
        unregisterlist.push_back(make_unregister(event,listener,listenerMethod));
    }

    template <class EventType>
    void unregisterbyEvent(EventType & event)
    {
        void * eventptr = static_cast<void *>(&event);
        for (UnregisterListType::iterator it = unregisterlist.begin(); it != unregisterlist.end(); ++it)
        {
            AbstractUnregister * u = *it;
            if(u->isevent(eventptr))
            {
                u->unregister();
                delete (u);
                *it = NULL;
            }
        }
        unregisterlist.remove(NULL);
    }

    virtual ~EventClientObject()
    {
        for (UnregisterListType::iterator it = unregisterlist.begin(); it != unregisterlist.end(); ++it)
        {
            AbstractUnregister * u = *it;
            u->unregister();
            delete (u);
        }
        unregisterlist.clear();
    }
};

/// class EventClient
/// If you want a class to be able to automatically unregister 
/// event listeners when destroyed, use this class through
/// inheritance. Use :
///     registerEvent( Event , &MyClass::method );

class EventClient : EventClientObject
{
    public:
    template <class EventType,typename ArgumentsType, class ListenerClass>
    void registerEvent(EventType & event, void (ListenerClass::*listenerMethod)(ArgumentsType&))
    {
        ListenerClass * listener = static_cast<ListenerClass *>(this);
        this->EventClientObject::registerEvent(listener,event,listenerMethod);
    }
    
    template <class EventType>
    void unregisterEvent(EventType & event)
    {
        this->EventClientObject::unregisterbyEvent(event);
    }

    virtual ~EventClient(){}
};

#endif // EVENTCLIENT_HPP_INCLUDED
