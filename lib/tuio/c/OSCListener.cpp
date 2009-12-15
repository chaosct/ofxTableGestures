
#include "OSCListener.h"
#include "osc/OscReceivedElements.h"
#include "ip/IpEndpointName.h"

namespace tuio {

void OSCListener::ProcessMessage(const osc::ReceivedMessage & m, const ::IpEndpointName & remoteEndpoint) {
  // Bouml preserved body begin 0002832A
  osc::ReceivedMessageArgumentStream as = m.ArgumentStream();
  ReceiveCall(m.AddressPattern(),as);
  // Bouml preserved body end 0002832A
}


} // namespace tuio
