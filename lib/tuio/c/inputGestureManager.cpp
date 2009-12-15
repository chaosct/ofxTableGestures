
#include "inputGestureManager.h"
#include "InputGesture.h"
#include "EventQueue.h"
#include "osc/OscReceivedElements.h"

#include "InputGestureClasses.h"

namespace tuio {

inputGestureManager::inputGestureManager() {
  // Bouml preserved body begin 000286AA
  queue = new EventQueue();

  InputGesture * i;

  //per a cada tipus de inputgesture, l'afegim a la llista:
  //i = new Exemple_de_imputgesture();
  //gestures.push_back(i);

    i = new InputGestureBasicFingers();
    gestures.push_back(i);

  // Bouml preserved body end 000286AA
}

void inputGestureManager::ReceiveCall(const char * addr, osc::ReceivedMessageArgumentStream & argList) {
  // Bouml preserved body begin 0002872A

  InputGesture * i;
  for(std::list<InputGesture *>::iterator  it = gestures.begin(); it != gestures.end(); it++)
  {
    i = *it;
    i->ReceiveCall(addr, argList.getCopy());
    for (std::list<TEvent *>::iterator it = i->events.begin(); it != i->events.end(); it++)
    {
        queue->push(*it);
    }
    i->events.clear();
  }

  // Bouml preserved body end 0002872A
}


} // namespace tuio
