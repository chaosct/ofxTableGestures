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
#include "EventQueue.h"
#include "TEvent.h"
#include <iostream>

namespace tuio {

EventQueue::EventQueue() {
  // Bouml preserved body begin 0002852A
  reader = 0;
  writer = 0;
  // Bouml preserved body end 0002852A
}

void EventQueue::push(TEvent * evt) {
  // Bouml preserved body begin 0002842A
  if( (writer +1)%QUEUE_SIZE ==  reader)
  {
    //discard messages when full
    std::cout << "Event Queue Full: discarding event :" << evt->name << std::endl;
    delete evt;
    return;
  }
  events[writer]=evt;
  writer = (writer + 1)%QUEUE_SIZE;
  // Bouml preserved body end 0002842A
}

TEvent * EventQueue::pop() {
  // Bouml preserved body begin 000284AA
  if( reader ==  writer)
  {
      //std::cout << "Final de la cua!" << std::endl;
      return NULL; // return NULL when empty
  }
  TEvent * evt = events[reader];
  reader = (reader + 1)%QUEUE_SIZE;
  return evt;
  // Bouml preserved body end 000284AA
}


} // namespace tuio
