#include "Dispatcher.h"

using namespace tuio;

void Dispatcher::processTevents(){
    TEvent * te;
    while((te = equeue->pop())!= NULL){
        for(std::list<Listener*>::iterator it = listeners_list.begin(); it != listeners_list.end(); it++){
            (*it)->processTevent(te);
        }
        delete te;
    }
}

void Dispatcher::tostring(){
    int i = 0;
    for(std::list<Listener*>::iterator it = listeners_list.begin(); it != listeners_list.end(); it++){
        i++;
    }
    std::cout<< "contains " << i << " elements"<< std::endl;
}
