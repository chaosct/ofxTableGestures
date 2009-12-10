
#include "EventQueue.h"
#include "TEvent.h"

namespace tuio {

EventQueue::EventQueue() {
  // Bouml preserved body begin 0002852A
  reader = 0;
  writer = 1;
  // Bouml preserved body end 0002852A
}

void EventQueue::push(TEvent * evt) {
  // Bouml preserved body begin 0002842A
  if( (writer +1)%1024 ==  reader)
  {
    //discard messages when full
    delete evt;
    return;
  }
  events[writer]=evt;
  writer = (writer + 1)%1024;
  // Bouml preserved body end 0002842A
}

TEvent * EventQueue::pop() {
  // Bouml preserved body begin 000284AA
  if( (reader +1)%1024 ==  writer)
    return NULL; // return NULL when empty
  Tevent * evt = events[reader];
  reader = (reader + 1)%1024;
  // Bouml preserved body end 000284AA
}


} // namespace tuio
