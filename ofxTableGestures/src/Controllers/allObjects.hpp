#ifndef ALLOBJECTS_HPP_INCLUDED
#define ALLOBJECTS_HPP_INCLUDED

#include "Graphic.hpp"
#include "InputGestureDirectObjects.hpp"

class allObjects: public OnTable < tuio::CanDirectObjects < Graphic > >
{
    public:
    std::set<tuio::DirectObject *> objects;
    void newObject(tuio::DirectObject * object)
    {
        objects.insert(object);
    }
    void removeObject(tuio::DirectObject * object)
    {
        objects.erase(object);
    }
};

#endif // ALLOBJECTS_HPP_INCLUDED
