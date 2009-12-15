#ifndef TUIO_INPUTGESTUREMANAGER_H
#define TUIO_INPUTGESTUREMANAGER_H


#include <list>
#include "OSCListener.h"

namespace tuio { class InputGesture; }
namespace tuio { class EventQueue; }
namespace osc { class ReceivedMessageArgumentStream; }

namespace tuio {

class inputGestureManager : public OSCListener {
  private:
    std::list<InputGesture *> gestures;


  public:
    inputGestureManager();
    EventQueue * queue;
    virtual void ReceiveCall(const char * addr, osc::ReceivedMessageArgumentStream & argList);

};

} // namespace tuio
#endif
