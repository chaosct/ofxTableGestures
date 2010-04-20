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
#include "tuioinput.hpp"
#include "inputGestureManager.hpp"
#include "EventQueue.hpp"


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

    //Only init once
    if(running)
        return;
    running = true;

    s = new UdpListeningReceiveSocket(
            IpEndpointName( IpEndpointName::ANY_ADDRESS, PORT ),
            gesturemanager );
    #ifndef WIN32
    pthread_create(&thread , NULL, ThreadFunc, this);
    #else
    DWORD threadId;
    thread = CreateThread( 0, 0, ThreadFunc, this, 0, &threadId );
    #endif

}

EventQueue  * tuioinput::getQueue() {
  // Bouml preserved body begin 0002862A
  return gesturemanager->queue;
  // Bouml preserved body end 0002862A
}

tuioinput::tuioinput():running(false){

    gesturemanager = inputGestureManager::get();

}

} // namespace tuio
