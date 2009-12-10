
#include "OSCListener.h"
#include "OscReceivedElements.h"
#include "IpEndpointName.h"

namespace tuio {

void OSCListener::ProcessMessage(const osc::ReceivedMessage & m, const ::IpEndpointName & remoteEndpoint) {
  // Bouml preserved body begin 0002832A
  ReceiveCall(m.AddressPattern(),m.ArgumentStream());
  // Bouml preserved body end 0002832A
}


} // namespace tuio
