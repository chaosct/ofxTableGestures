#ifndef TUIO_EVENTQUEUE_H
#define TUIO_EVENTQUEUE_H


namespace tuio { class TEvent; } 

namespace tuio {

class EventQueue {
  private:
    TEvent * events[1024];

    unsigned int reader;

    unsigned int writer;


  public:
    EventQueue();

    void push(TEvent * evt);

    TEvent * pop();

};

} // namespace tuio
#endif
