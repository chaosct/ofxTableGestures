#ifndef TUIO_EVENTQUEUE_H
#define TUIO_EVENTQUEUE_H


#include "TEvent.h"

#define QUEUE_SIZE 1024

namespace tuio {

class EventQueue {
  private:
    TEvent * events[QUEUE_SIZE];

    unsigned int reader;

    unsigned int writer;


  public:
    EventQueue();

    void push(TEvent * evt);

    TEvent * pop();

};

} // namespace tuio
#endif
