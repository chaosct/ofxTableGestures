/*

    OF-TangibleFramework . Framework for Taller de Sistemes Interactius I
    Universitat Pompeu Fabra

    Copyright (c) 2009 Carles F. Julià <carles.fernandez@upf.edu>

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
#ifndef TUIOAPP_H_INCLUDED
#define TUIOAPP_H_INCLUDED

#define TRegistraCallback(T,TE) Base::registerCallback(Singleton<TE>::Instance().name,new tuio::Callback<T>(this,&T::EP_##TE ))
#define TEventHandler(en) void EP_##en (tuio::TEvent * evt)


#include "EventQueue.hpp"
#include "tuioinput.hpp"
#include "InputGesture.hpp"
#include "inputGestureManager.hpp"
#include <iostream>

#define BOOST_FUSION_INVOKE_PROCEDURE_MAX_ARITY 15
#define FUSION_MAX_VECTOR_SIZE 15

#include "boost/fusion/include/sequence.hpp"
#include "boost/fusion/include/make_vector.hpp"
#include "boost/fusion/include/push_front.hpp"
#include "boost/fusion/include/invoke_procedure.hpp"
#include "boost/static_assert.hpp"
#include "boost/mpl/assert.hpp"
#include "boost/type_traits/is_base_of.hpp"

namespace tuio
{

class GenericCallback
{
public:
    virtual void run(TEvent * )=0;
};


//from http://stackoverflow.com/questions/1284014/callback-in-c-template-member#answer-1284047
template<typename C>
class Callback : public GenericCallback
{
      public:
  // constructs a callback to a method in the context of a given object
  Callback(C* object, void (C::*method)(TEvent *))
    : o(object),m(method) {}
  // calls the method
  void run(TEvent * te) {
    (o ->* m) (te);
  }
  private:
  // container for the pointer to method
    C* o;
    void (C::*m)(TEvent *);
};

///This Callback doesn't need handlers, but it needs to use AEvent
template<typename C, typename M, typename E>
class AlternateCallback : public GenericCallback
{
      public:
  // constructs a callback to a method in the context of a given object
  AlternateCallback(C* object, M method)
    : o(object),m(method) {}
  // calls the method
  void _run(TEvent * te)
  {
    E * e =  static_cast<E*>(te);
    boost::fusion::invoke_procedure(m,boost::fusion::push_front(e->s, o));
  }
  void run(TEvent * te){_run(te);}
  private:
  // container for the pointer to method
    C* o;
    M m;
};

#define _SimpleGetEventName(canclass,method) Event_##canclass##method

#define SimpleDeclareEvent(canclass,method,...) DeclareEvent(_SimpleGetEventName(canclass,method),__VA_ARGS__)
#define SimpleCallEvent(canclass,method,arguments) this->events.push_back(SimpleMakeEvent(canclass,method,arguments))
#define SimpleMakeEvent(canclass,method,arguments) makeEvent(_SimpleGetEventName(canclass,method),arguments)
#define SimpleRegisterEvent(canclass,method) _SimpleGetEventName(canclass,method)::registerCallback(this,&canclass::method);

#define DeclareEvent(eventname,...) class eventname : \
    public AEvent<eventname,boost::fusion::vector<__VA_ARGS__> >\
        {   typedef boost::fusion::vector<__VA_ARGS__> SequenceType;\
            public: eventname(SequenceType v = SequenceType()):AEvent<eventname,SequenceType>(v){}};

#define makeEvent(classname,arguments) new classname(boost::fusion::make_vector arguments)



template <typename E, typename Sequence>
class AEvent : public TEvent
{
    public:
    AEvent(Sequence S):s(S)
    {
        name = EventTypes::Instance().get_number<E>();
    }
    Sequence s;
    template<typename C,typename M>
    static AlternateCallback<C,M,AEvent> * makeCallback(C* object, M method)
    {
        return new AlternateCallback<C,M,AEvent>(object,method);
    }
    template<typename TA,typename M>
    static void registerCallback(TA *ta,M m)
    {
        ta->registerCallback(EventTypes::Instance().get_number<E>(), makeCallback(ta,m));
    }
};



class VoidClass {};
class tuioAppBase {};

typedef std::vector<GenericCallback * > eventprocessorsType;

template< class Base = VoidClass>
class tuioApp : public Base, tuioAppBase
{
private:
    eventprocessorsType eventprocessors;
    ///To know if we are in the osc thread or in the app's one. Gestures only live in osc thread.
    bool isGestureListener;
protected:
    ///List of IG that create events we can process
    std::list<InputGesture *> feeders;
public:
    ///Do not allow to use this template twice on the same class
    BOOST_MPL_ASSERT_NOT(( boost::is_base_of<tuioAppBase,Base> ));

    tuioApp( bool _isGestureListener = false):isGestureListener(_isGestureListener)
    {
        ///TODO: better sizing
        eventprocessors.resize(100,NULL);
    }

    virtual ~tuioApp()
    {
        for (std::list<InputGesture *>::iterator it = feeders.begin();
                it != feeders.end(); ++it)
                {
                    InputGesture * ig = *it;
                    ig->nonGestureListeners--;
                }
    }

    void processTevent(TEvent * te)
    {
        if (eventprocessors[te->name])
            eventprocessors[te->name]->run(te);
    }

    void registerCallback(unsigned int n, GenericCallback * callback)
    {
        if(eventprocessors.size() <= n)
        {
            std::cout << "tuioApp: Fatal! register number out of range!" << std::endl;
        }
        eventprocessors[n]=callback;
    }


    void registerInputGesture(InputGesture * IG)
    {
        inputGestureManager::Instance().addGesture(IG);
        feeders.push_back(IG);
        if(!isGestureListener)
        {
            IG->nonGestureListeners++;
        }
    }


    template< typename I>
    void registerIG()
    {
        registerInputGesture(Singleton<I>::get());
    }

};

class CompositeGesture : public tuioApp< InputGesture >
{
    public:
    CompositeGesture():tuioApp< InputGesture >(true){}
    virtual void ProcessBundle( const osc::ReceivedBundle& b, const IpEndpointName& remoteEndpoint )
    {
        for (std::list<InputGesture *>::iterator it = feeders.begin();
                it != feeders.end(); ++it)
        {
            InputGesture * ig = *it;
            for (std::list<TEvent *>::iterator it = ig->events.begin() ; it != ig->events.end() ; ++it)
            {
                processTevent(*it);
            }
        }
        InputGesture::ProcessBundle(b,remoteEndpoint);
    }
};

}
#endif // TUIOAPP_H_INCLUDED
