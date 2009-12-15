#ifndef TUIO_OSCLISTENER_H
#define TUIO_OSCLISTENER_H



#include "osc/OscPacketListener.h"

//namespace osc { class ReceivedMessageArgumentStream; }
//namespace osc { class ReceivedMessage; class IpEndpointName;}

namespace tuio {

class OSCListener : public osc::OscPacketListener {
  public:
    virtual  void ReceiveCall(const char * addr, osc::ReceivedMessageArgumentStream & argList) = 0;


  protected:
    virtual void ProcessMessage(const osc::ReceivedMessage & m, const ::IpEndpointName & remoteEndpoint);

};

} // namespace tuio
#endif
