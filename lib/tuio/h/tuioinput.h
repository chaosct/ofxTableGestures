#ifndef TUIO_TUIOINPUT_H
#define TUIO_TUIOINPUT_H


namespace tuio { class inputGestureManager; } 
namespace tuio { class EventQueue; } 

namespace tuio {

class tuioinput {
  private:
    inputGestureManager * gesturemanager;


  public:
    void init();

    EventQueue  * getQueue();

};

} // namespace tuio
#endif
