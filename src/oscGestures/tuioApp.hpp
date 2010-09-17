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

#include "EventQueue.hpp"
#include "tuioinput.hpp"
#include "InputGesture.hpp"
#include "inputGestureManager.hpp"
#include <iostream>
#include <map>
#include <cassert>

#define BOOST_FUSION_INVOKE_PROCEDURE_MAX_ARITY 16
#define FUSION_MAX_VECTOR_SIZE 16

#include "boost/fusion/include/sequence.hpp"
#include "boost/fusion/include/make_vector.hpp"
#include "boost/fusion/include/push_front.hpp"
#include "boost/fusion/include/invoke_procedure.hpp"
#include "boost/static_assert.hpp"
#include "boost/mpl/assert.hpp"
#include "boost/type_traits/is_base_of.hpp"
#include "Area.hpp"
#include "GlobalConfig.hpp"

namespace tuio
{

class GenericCallback
{
public:
    virtual void run(TEvent * )=0;
};


template<typename C, typename M, typename E>
class Callback : public GenericCallback
{
      public:
  // constructs a callback to a method in the context of a given object
  Callback(C* object, M method)
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
#define _makeEvent(classname,arguments) new classname(boost::fusion::make_vector arguments)
#define SimpleDeclareEvent(canclass,method,...) _DeclareEvent(_SimpleGetEventName(canclass,method),__VA_ARGS__)
#define SimpleCallEvent(canclass,method,arguments) this->events.push_back(SimpleMakeEvent(canclass,method,arguments))
#define SimpleMakeEvent(canclass,method,arguments) _makeEvent(_SimpleGetEventName(canclass,method),arguments)
#define SimpleRegisterEvent(canclass,method) _SimpleGetEventName(canclass,method)::registerCallback(this,&canclass::method);

#ifdef DEBUG
#define _DeclareEvent_Debug_Line(eventname)  debugName = #eventname ;
#else
#define _DeclareEvent_Debug_Line(eventname)
#endif

#define _DeclareEvent(eventname,...) class eventname : \
    public AEvent<eventname,boost::fusion::vector<__VA_ARGS__> >\
        {   typedef boost::fusion::vector<__VA_ARGS__> SequenceType;\
            public: eventname(SequenceType v = SequenceType()): \
            AEvent<eventname,SequenceType>(v){\
            _DeclareEvent_Debug_Line(eventname) \
            }};





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
    static Callback<C,M,AEvent> * makeCallback(C* object, M method)
    {
        return new Callback<C,M,AEvent>(object,method);
    }
    template<typename TA,typename M>
    static void registerCallback(TA *ta,M m)
    {
        ta->registerCallback(EventTypes::Instance().get_number<E>(), makeCallback(ta,m));
    }
};

class InputGestureProxy: public inputGestureManagerBase, public InputGesture
{
    public:
    SetDebugName(InputGestureProxy)
    void ProcessBundle( const osc::ReceivedBundle& b, const IpEndpointName& remoteEndpoint )
    {
        IGMProcessBundle( b, remoteEndpoint );
    }
};

class VoidClass {};
class tuioAreaBase {
    public:
    inputGestureManagerBase * manager;
    virtual void processTevent(TEvent * te){}
};

class tuioAreaDelivery: public Singleton<tuioAreaDelivery>
{
    std::map<Area *,std::list<tuioAreaBase *> >  tareas;
    public:
    void RegisterTA(Area *a,tuioAreaBase *ta)
    {
        tareas[a].push_back(ta);
    }
    void UnregisterTA(Area * a,tuioAreaBase *ta)
    {
        tareas[a].remove(ta);
        if(tareas[a].size() == 0)
        {
            inputGestureManager::Instance().removeGesture(getGestureByArea<InputGestureProxy>(a));
        }
    }
    void processTevents()
    {
        for (std::map<Area *,std::list<tuioAreaBase *> >::iterator it = tareas.begin();
                it != tareas.end(); ++it)
                {
                    std::list<tuioAreaBase *> & l = it->second;
                    if(l.size() > 0)
                    {
                        inputGestureManagerBase * manager = l.front()->manager;
                        processTevents(manager,l);
                    }
                }
    }
    void processTevents(inputGestureManagerBase * manager,std::list<tuioAreaBase *> & l)
    {
        TEvent * te;
        while((te = manager->queue->pop())!= NULL){
            for(std::list<tuioAreaBase *>::iterator it = l.begin(); it != l.end(); ++it){
                (*it)->processTevent(te);
            }
            delete te;
        }
    }

    template<typename GestureType>
    static GestureType * getGestureByArea(Area * a)
    {
       static std::map<Area*, GestureType *> pairs;
       GestureType * ig;
       if(pairs.find(a) == pairs.end())
       {
           ig = new GestureType();
           pairs[a] = ig;
       }
       else
       {
           ig = pairs[a];
       }
       return ig;
    }
};



typedef std::vector<GenericCallback * > eventprocessorsType;

template< class Base = VoidClass>
class tuioArea : public Base, public tuioAreaBase
{
    private:
    eventprocessorsType eventprocessors;
    ///To know if we are in the osc thread or in the app's one. Gestures only live in osc thread.
    bool isGestureListener;

    bool registered;

    void registerInputGesture(InputGesture * IG)
    {
        assert(manager != NULL);
        manager->addGesture(IG);
        if(std::find(feeders.begin(),feeders.end(),IG) == feeders.end())
            feeders.push_back(IG);
        if(!isGestureListener)
        {
            IG->nonGestureListeners++;
        }
    }

    protected:
    ///List of IG that create events we can process
    std::list<InputGesture *> feeders;
    Area * area;

    public:
    ///Do not allow to use this template twice on the same class
    BOOST_MPL_ASSERT_NOT(( boost::is_base_of<tuioAreaBase,Base> ));

    void processTevent(TEvent * te)
    {
        if (eventprocessors[te->name])
            eventprocessors[te->name]->run(te);
    }

    void registerCallback(unsigned int n, GenericCallback * callback)
    {
        if(eventprocessors.size() <= n)
        {
            std::cout << "tuioArea: Fatal! register number out of range!" << std::endl;
        }
        eventprocessors[n]=callback;
    }

    void _Register(Area * a = NULL);
    void Register(Area * a )
    {
        _Register(a);
        tuioAreaDelivery::Instance().RegisterTA(area,this);
    }

    tuioArea( bool _isGestureListener = false):
    isGestureListener(_isGestureListener),
    area(NULL)
    {
        manager=NULL;
        ///TODO: better sizing
        eventprocessors.resize(100,NULL);
    }

    virtual ~tuioArea()
    {
        for (std::list<InputGesture *>::iterator it = feeders.begin();
                it != feeders.end(); ++it)
                {
                    InputGesture * ig = *it;
                    ig->nonGestureListeners--;
                }
        if(registered)
            tuioAreaDelivery::Instance().UnregisterTA(area,this);
    }

    template< typename I>
    void registerIG()
    {
        I * ig = tuioAreaDelivery::Instance().getGestureByArea<I>(area);
        ig->Register(area);
        registerInputGesture(ig);
    }
    template< typename I>
    void registerIGA()
    {
        I * ig = tuioAreaDelivery::Instance().getGestureByArea<I>(area);
        ig->area = area;
        ig->Register(area);
        registerInputGesture(ig);
    }
};

template<typename T>
void tuioArea<T>::_Register(Area * a )
{
    area = a;
    if(!area)
    {
        if(GlobalConfig::getRef("GLOBAL:ROUNDTABLE",1))
            area = RoundTableArea::Create();
        else
            area = NoArea::Create();

    }
    InputGestureProxy * p = tuioAreaDelivery::Instance().getGestureByArea<InputGestureProxy>(area);
    inputGestureManager::Instance().addGesture(p);
    manager = static_cast<inputGestureManagerBase *>(p);
    registered = true;
}

class CompositeGesture : public tuioArea< InputGesture >
{
    public:
    CompositeGesture():tuioArea< InputGesture >(true){}
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
    void Register(Area * a = NULL)
    {
        _Register(a);
    }
};

}

#endif // TUIOAPP_H_INCLUDED
