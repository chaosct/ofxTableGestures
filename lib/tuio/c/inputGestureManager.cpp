/*

    TSIframework . Framework for Taller de Sistemes Interactius I
    Universitat Pompeu Fabra

    Copyright (c) 2009 Carles F. Julià <carles.fernandez@upf.edu>

    Permission is hereby granted, free of charge, to any person
    obtaining a copy of this software and associated documentation
    files (the "Software"), to deal in the Software without
    restriction, including without limitation the rights to use,
    copy, modify, merge, publish, distribute, sublicense, and/or sell
    copies of the Software, and to permit persons to whom the
    Software is furnished to do so, subject to the following
    conditions:

    The above copyright notice and this permission notice shall be
    included in all copies or substantial portions of the Software.

    THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
    EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES
    OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
    NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT
    HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
    WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
    FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
    OTHER DEALINGS IN THE SOFTWARE.

*/
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
    i = new InputGestureDirectFingers();
    gestures.push_back(i);
    i = new InputGestureBasicObjects();
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
