#ifndef EVENTS_HPP_INCLUDED
#define EVENTS_HPP_INCLUDED

class Graphic;

struct EventArgs {
    Graphic * target;
    EventArgs():target(NULL){}
};

class CompositeGesture {};

#endif // EVENTS_HPP_INCLUDED
