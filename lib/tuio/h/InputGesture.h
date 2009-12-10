#ifndef TUIO_INPUTGESTURE_H
#define TUIO_INPUTGESTURE_H


#include "OSCListener.h"
#include <list>
using namespace std;

namespace tuio { class TEvent; } 

namespace tuio {

class InputGesture : public OSCListener {
  private:
    list<TEvent *> events;

};

} // namespace tuio
#endif
