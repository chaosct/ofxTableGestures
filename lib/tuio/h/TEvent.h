#ifndef TUIO_TEVENT_H
#define TUIO_TEVENT_H


#include <string>
using namespace std;
#include <vector>
using namespace std;

namespace tuio {

//Els destructors s'usen a través d'herencia
class TEvent {
  private:
    string name;

    vector<void *> args;

};

} // namespace tuio
#endif
