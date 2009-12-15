
#include "tuioinput.h"
#include "inputGestureManager.h"
#include "EventQueue.h"


#define PORT 3333


#ifndef WIN32
static void* ThreadFunc( void* obj )
#else
static DWORD WINAPI ThreadFunc( LPVOID obj )
#endif
{
	static_cast<tuio::tuioinput*>(obj)->s->Run();
	return 0;
};



namespace tuio {

void tuioinput::init() {
  // Bouml preserved body begin 000285AA
    s = new UdpListeningReceiveSocket(
            IpEndpointName( IpEndpointName::ANY_ADDRESS, PORT ),
            gesturemanager );
    #ifndef WIN32
    pthread_create(&thread , NULL, ThreadFunc, this);
    #else
    DWORD threadId;
    thread = CreateThread( 0, 0, ThreadFunc, this, 0, &threadId );
    #endif
  // Bouml preserved body end 000285AA
}

EventQueue  * tuioinput::getQueue() {
  // Bouml preserved body begin 0002862A
  return gesturemanager->queue;
  // Bouml preserved body end 0002862A
}

tuioinput::tuioinput(){

    gesturemanager = new inputGestureManager();

}

} // namespace tuio
