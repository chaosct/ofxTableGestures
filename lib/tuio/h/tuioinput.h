#ifndef TUIO_TUIOINPUT_H
#define TUIO_TUIOINPUT_H


#ifndef WIN32
#include <pthread.h>
#include <sys/time.h>
#else
#include <windows.h>
#endif

#include "ip/UdpSocket.h"

namespace tuio { class inputGestureManager; }
namespace tuio { class EventQueue; }

namespace tuio {

class tuioinput {
  private:
    inputGestureManager * gesturemanager;

#ifndef WIN32
    pthread_t thread;
#else
    HANDLE thread;
#endif

  public:
    void init();
    tuioinput();
    EventQueue  * getQueue();
    UdpListeningReceiveSocket *s;
};

} // namespace tuio
#endif
