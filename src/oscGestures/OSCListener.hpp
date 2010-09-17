/*

    ofxTableGestures (formerly OF-TangibleFramework)
    Developed for Taller de Sistemes Interactius I
    Universitat Pompeu Fabra

    Copyright (c) 2010 Carles F. Julià <carles.fernandez@upf.edu>

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

#ifndef TUIO_OSCLISTENER_H
#define TUIO_OSCLISTENER_H

#include "OscPacketListener.h"


namespace tuio {

class OSCListener : public osc::OscPacketListener {
  public:
    virtual  void ReceiveCall(const char * addr, osc::ReceivedMessageArgumentStream & argList){};

  public:
    virtual void ProcessBundle( const osc::ReceivedBundle& b,
				const IpEndpointName& remoteEndpoint ){osc::OscPacketListener::ProcessBundle(b,remoteEndpoint);}
  protected:
    virtual void ProcessMessage(const osc::ReceivedMessage & m, const ::IpEndpointName & remoteEndpoint);

};

} // namespace tuio
#endif
