#include "InputListener.h"

using namespace tuio;

Listener::Listener(){
    Dispatcher::Instance().AddListener(this);
}

Listener::~Listener(){
    Dispatcher::Instance().RemoveListener(this);
}

