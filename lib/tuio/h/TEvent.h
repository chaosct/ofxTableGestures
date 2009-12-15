#ifndef TUIO_TEVENT_H
#define TUIO_TEVENT_H


#include <string>
#include <vector>
#include <iostream>

namespace tuio {

//Els destructors s'usen a través d'herencia
class TEvent {
  public:
     std::string name;

    //std::vector<void *> args;
    ~TEvent()
    {
        std::cout << "Destruint " << name << std::endl;
    }
};

} // namespace tuio
#endif
