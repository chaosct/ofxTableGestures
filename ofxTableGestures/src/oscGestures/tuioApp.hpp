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

#define TRegistraCallback(T,TE) Base::registerCallback(Singleton<TE>::Instance().name,new Callback<T>(this,&T::EP_##TE ))
#define TEventHandler(en) void EP_##en (TEvent * evt)


#include "EventQueue.hpp"
#include "tuioinput.hpp"
#include "InputGesture.hpp"
#include "inputGestureManager.hpp"
#include <iostream>

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



class VoidClass{};

typedef std::vector<GenericCallback * > eventprocessorsType;

template< class Base = VoidClass>
class tuioApp : public Base
{
private:
    eventprocessorsType eventprocessors;
    ///To know if we are in the osc thread or in the app's one. Gestures only live in osc thread.
    bool isGestureListener;
protected:
    ///List of IG that create events we can process
    std::list<InputGesture *> feeders;
public:
    tuioApp( bool _isGestureListener = false):isGestureListener(_isGestureListener)
    {
        ///TODO: better sizing
        eventprocessors.resize(100,NULL);
    }

    ~tuioApp()
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
        inputGestureManager::addGesture(IG);
        feeders.push_back(IG);
        if(!isGestureListener)
        {
            IG->nonGestureListeners++;
        }
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
