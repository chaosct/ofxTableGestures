#include "InputListener.h"

using namespace tuio;

Listener::Listener(){
    eventprocessors.resize(100,NULL);
    Dispatcher::Instance().AddListener(this);
}

Listener::~Listener(){
    Dispatcher::Instance().RemoveListener(this);
}

eventprocessorsType & Listener::getEP(){
    return eventprocessors;
}

void Listener::processTevent(TEvent * te){
    if (eventprocessors[te->name])
        eventprocessors[te->name]->run(te);
}
