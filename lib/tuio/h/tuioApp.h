#ifndef TUIOAPP_H_INCLUDED
#define TUIOAPP_H_INCLUDED

#define TCallBack(T,m) class Callback_##m: public GenericCallback \
{ \
    public: \
    Callback_##m (T * i) \
    { \
        instance = i; \
    } \
    T * instance ; \
    void run(TEvent * evt) \
    { \
       instance->EP_##m (evt); \
    } \
}

#define TRegistraCallback(en) Base::getEP()[en] = new Callback_##en(this)

#define TEventHandler(en) void EP_##en (TEvent * evt)


#include "EventQueue.h"

namespace tuio
{

class GenericCallback
{
public:
    virtual void run(TEvent * )=0;
};

typedef std::vector<GenericCallback * > eventprocessorsType;

template< class Base >
class tuioApp : public Base
{
private:
    eventprocessorsType eventprocessors;
public:
    EventQueue * equeue;

    tuioApp()
    {
        //TODO: fora magic number o fer servir map
        eventprocessors.resize(10,NULL);
    }

    void processTevents()
    {
        TEvent * te;
        while((te = equeue->pop())!= NULL)
        {
            if (eventprocessors[te->name])
                eventprocessors[te->name]->run(te);
            delete te;
        }
    }

    eventprocessorsType & getEP()
    {
        return eventprocessors;
    }
};

}
#endif // TUIOAPP_H_INCLUDED
