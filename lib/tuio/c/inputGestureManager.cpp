
#include "inputGestureManager.h"
#include "InputGesture.h"
#include "EventQueue.h"
#include "OscReceivedElements.h"

namespace tuio {

inputGestureManager::inputGestureManager() {
  // Bouml preserved body begin 000286AA
  queue = new EventQueue();
  
  InputGesture * i;
  
  //per a cada tipus de inputgesture, l'afegim a la llista:
  //i = new Exemple_de_imputgesture();
  //gestures.push_back(i);
  
  // Bouml preserved body end 000286AA
}

 inputGestureManager::ReceiveCall(char addr, const osc::ReceivedMessageArgumentStream & argList) {
  // Bouml preserved body begin 0002872A
  
  InputGesture * i;
  for(list<InputGesture *>::iterator  it = gestures.begin(); it != gestures.end(); it++)
  {
    i = *it;
    i->ReceiveCall(addr, argList);
    //TODO:collect resultats
  }
  
  // Bouml preserved body end 0002872A
}


} // namespace tuio
