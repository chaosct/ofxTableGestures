#ifndef TUIO_OSCLISTENER_H
#define TUIO_OSCLISTENER_H


#include "PacketListener.h"
#include "OscPacketListener.h"

namespace osc { class ReceivedMessageArgumentStream; } 
namespace osc { class ReceivedMessage; } 
class IpEndpointName;

namespace tuio {

class OSCListener : public ::PacketListener, public osc::OscPacketListener {
  public:
    virtual  ReceiveCall(char * addr, const osc::ReceivedMessageArgumentStream & argList) = 0;


  protected:
    virtual void ProcessMessage(const osc::ReceivedMessage & m, const ::IpEndpointName & remoteEndpoint);

};

} // namespace tuio
#endif
