#ifndef TUIO_INPUTGESTURE_H
#define TUIO_INPUTGESTURE_H


#include "OSCListener.h"
#include <list>

#include "TEvent.h"



namespace tuio {

class InputGesture : public OSCListener {
  public:
    std::list<TEvent *> events;

};

} // namespace tuio
#endif
