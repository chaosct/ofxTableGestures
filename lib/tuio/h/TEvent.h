#ifndef TUIO_TEVENT_H
#define TUIO_TEVENT_H



#include <vector>
#include <iostream>


namespace tuio {

enum EventType {
    //InputGestureBasicFingers
    event_finger_remove, event_finger_move, event_finger_new
};

//Els destructors s'usen a través d'herencia
class TEvent {
  public:
     EventType name;

    //std::vector<void *> args;
    TEvent(EventType n):name(n){}
    ~TEvent()
    {
        //std::cout << "Destruint " << name << std::endl;
    }
};

} // namespace tuio


#endif
