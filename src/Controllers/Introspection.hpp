#ifndef INTROSPECTION_HPP_INCLUDED
#define INTROSPECTION_HPP_INCLUDED

#include "InputGestureDirectObjects.hpp"
#include "Graphic.hpp"
#include "SimpleObjectController.hpp"

template<typename T>
class Introspection: public SimpleObjectController<T>
{
    public:
    Introspection(const std::string & addr,unsigned int f_id,T Min,T Max):
    SimpleObjectController<T>(GlobalConfig::getRef<T>(addr) ,f_id,Min,Max){}
};

#endif // INTROSPECTION_HPP_INCLUDED
