#ifndef ALLFINGERS_HPP_INCLUDED
#define ALLFINGERS_HPP_INCLUDED

#include "Graphic.hpp"
#include "InputGestureDirectFingers.hpp"
class allFingers: public OnTable < tuio::CanDirectFingers < Graphic > >, public std::set<tuio::DirectFinger *>
{
    public:
    void newCursor(tuio::DirectFinger * object)
    {
        insert(object);
    }
    void removeCursor(tuio::DirectFinger * object)
    {
        erase(object);
    }
};

#endif // ALLFINGERS_HPP_INCLUDED
