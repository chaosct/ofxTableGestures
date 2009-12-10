#ifndef TUIO_INPUTGESTUREMANAGER_H
#define TUIO_INPUTGESTUREMANAGER_H


#include <list>
using namespace std;
#include "OSCListener.h"

namespace tuio { class InputGesture; } 
namespace tuio { class EventQueue; } 
namespace osc { class ReceivedMessageArgumentStream; } 

namespace tuio {

class inputGestureManager : public OSCListener {
  private:
    list<InputGesture *> gestures;

    EventQueue * queue;


  public:
    inputGestureManager();

    virtual  ReceiveCall(char * addr, const osc::ReceivedMessageArgumentStream & argList);

};

} // namespace tuio
#endif
