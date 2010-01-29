#ifndef INPUTGESTUREDUMMYCLICK_H_INCLUDED
#define INPUTGESTUREDUMMYCLICK_H_INCLUDED

#include "ofMain.h"
#include "InputGestureBasicFingers.h"
#include "TEvent.h"
#include <map>

namespace tuio
{

class tapData
{
    public:
    float tstamp;
    float x,y;
    float maxx, maxy, minx, miny;
    tapData(float _x,float _y,float t):tstamp(t),x(_x),y(_y),maxx(x),maxy(y),minx(x),miny(y){}
    void update(float _x,float _y)
    {
        maxx = max(maxx,_x);
        maxy = max(maxy,_y);
        minx = min(minx,_x);
        miny = min(miny,_y);
    }
    bool istap()
    {
        float now = ofGetElapsedTimef();
        float dt = now - tstamp;
        if (dt > 0.2) return false;
        if (max(maxx-minx,maxy-miny) > 0.01) return false;
        return true;
    }
};

class TeventTap : public TTEvent <TeventTap>
{
public:
    float duration;
    float x,y;
};

class InputGestureTap : public CanBasicFingers < CompositeGesture >
{
    std::map<int32,tapData *> tstamps;

public:

    //From CanBasicFingers
    void addTuioCursor(int32 id, float xpos,float ypos,float xspeed,float yspeed,float maccel)
    {
        tstamps[id] = new tapData(xpos,ypos,ofGetElapsedTimef());
    }
    void updateTuioCursor(int32 id, float xpos,float ypos,float xspeed,float yspeed,float maccel)
    {
        tstamps[id]->update(xpos,ypos);
    }
    void removeTuioCursor(int32 id)
    {
        if (tstamps[id]->istap())
        {
            TeventTap * evt = new TeventTap();
            evt->x = tstamps[id]->x;
            evt->y = tstamps[id]->y;
            events.push_back(evt);
        }
    }
};

template <class Base>
class CanTap : public  Base
{
public:
    //Interface redefined by ofApp
    virtual void tap(float x, float y) {}

    //processing events callbacks
    TEventHandler(TeventTap)
    {
        TeventTap * e = static_cast<TeventTap *>(evt);
        tap(e->x,e->y);
    }

    //registering
    CanTap()
    {
        TRegistraCallback(CanTap,TeventTap);
        Base::registerInputGesture(Singleton<InputGestureTap>::get());
    }

};

}
#endif // INPUTGESTUREDUMMYCLICK_H_INCLUDED
