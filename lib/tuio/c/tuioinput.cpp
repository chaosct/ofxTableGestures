
#include "tuioinput.h"
#include "inputGestureManager.h"
#include "EventQueue.h"

namespace tuio {

void tuioinput::init() {
  // Bouml preserved body begin 000285AA
  gesturemanager = new inputGestureManager();
  // Bouml preserved body end 000285AA
}

EventQueue  * tuioinput::getQueue() {
  // Bouml preserved body begin 0002862A
  return gesturemanager->queue;
  // Bouml preserved body end 0002862A
}


} // namespace tuio
