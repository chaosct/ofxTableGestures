#ifndef EVENTS_HPP_INCLUDED
#define EVENTS_HPP_INCLUDED

class Graphic;

struct EventArgs {
    const Graphic * target;
    EventArgs():target(NULL){}
};

class CompositeGesture {};

struct commonIdArgs : public virtual EventArgs
{
    int id;
};

#endif // EVENTS_HPP_INCLUDED
