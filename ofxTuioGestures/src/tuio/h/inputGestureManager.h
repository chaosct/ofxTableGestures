/*

    OF-TangibleFramework . Framework for Taller de Sistemes Interactius I
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

#ifndef TUIO_INPUTGESTUREMANAGER_H
#define TUIO_INPUTGESTUREMANAGER_H


#include <list>
#include <algorithm>
#include "OSCListener.h"
#include "EventQueue.h"
#include "InputGesture.h"


namespace tuio {

class inputGestureManager : public OSCListener {
  private:
    std::list<InputGesture *> gestures;
    static inputGestureManager * instance;
    blocklessQueue<InputGesture ,1024> gesturesToAdd;
    static void addPendingGestures()
    {
        InputGesture *IG;
        while((IG = instance->gesturesToAdd.pop())!= NULL){
            if (std::find (instance->gestures.begin(), instance->gestures.end(), IG) == instance->gestures.end())
                instance->gestures.push_back(IG);
        }
    }
  public:
    EventQueue * queue;

    static void addGesture(InputGesture *IG)
    {
        instance->gesturesToAdd.push(IG);
    }
    inputGestureManager();
    virtual void ReceiveCall(const char * addr, osc::ReceivedMessageArgumentStream & argList);

};

} // namespace tuio
#endif
