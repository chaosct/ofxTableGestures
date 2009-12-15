
#include "EventQueue.h"
#include "TEvent.h"
#include <iostream>

namespace tuio {

EventQueue::EventQueue() {
  // Bouml preserved body begin 0002852A
  reader = 0;
  writer = 0;
  // Bouml preserved body end 0002852A
}

void EventQueue::push(TEvent * evt) {
  // Bouml preserved body begin 0002842A
  if( (writer +1)%QUEUE_SIZE ==  reader)
  {
    //discard messages when full
    std::cout << "Event Queue Full: discarding event :" << evt->name << std::endl;
    delete evt;
    return;
  }
  events[writer]=evt;
  writer = (writer + 1)%QUEUE_SIZE;
  // Bouml preserved body end 0002842A
}

TEvent * EventQueue::pop() {
  // Bouml preserved body begin 000284AA
  if( reader ==  writer)
  {
      //std::cout << "Final de la cua!" << std::endl;
      return NULL; // return NULL when empty
  }
  TEvent * evt = events[reader];
  reader = (reader + 1)%QUEUE_SIZE;
  return evt;
  // Bouml preserved body end 000284AA
}


} // namespace tuio
