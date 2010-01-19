#ifndef INPUTGESTUREDUMMYCLICK_H_INCLUDED
#define INPUTGESTUREDUMMYCLICK_H_INCLUDED

#include "InputGestureBasicFingers.h"
#include "TEvent.h"
#include <map>

namespace tuio
{

class tabcursor
{
    public:
    float tstamp;
    float x,y;
    float maxx, maxy, minx, miny;
    tabcursor(float _x,float _y,float t):tstamp(t),x(_x),y(_y),maxx(x),maxy(y),minx(x),miny(y){}
    void update(float _x,float _y)
    {
        maxx = max(maxx,_x);
        maxy = max(maxy,_y);
        minx = min(minx,_x);
        miny = min(miny,_y);
    }
    bool istab()
    {
        float now = ofGetElapsedTimef();
        float dt = now - tstamp;
        if (dt > 0.2) return false;
        if (max(maxx-minx,maxy-miny) > 0.01) return false;
        return true;
    }
};

class TeventDummyTabTabed : public TTEvent <TeventDummyTabTabed>
{
public:
    float duration;
    float x,y;
};

class InputGestureDummyTab : public CanBasicFingers < tuioApp <InputGesture> >
{
    std::map<int32,tabcursor *> tstamps;
    InputGestureBasicFingers * basicfingers;
public:
    InputGestureDummyTab()
    {
        basicfingers = Singleton< InputGestureBasicFingers>::get();
    }
    virtual void ReceiveCall(const char * addr, osc::ReceivedMessageArgumentStream & argList)
    {
        for (std::list<TEvent *>::iterator it = basicfingers->events.begin() ; it != basicfingers->events.end() ; ++it)
        {
            processTevent(*it);
        }
    }
    //From CanBasicFingers
    void addTuioCursor(int32 id, float xpos,float ypos,float xspeed,float yspeed,float maccel)
    {
        tstamps[id] = new tabcursor(xpos,ypos,ofGetElapsedTimef());
    }
    void updateTuioCursor(int32 id, float xpos,float ypos,float xspeed,float yspeed,float maccel)
    {
        tstamps[id]->update(xpos,ypos);
    }
    void removeTuioCursor(int32 id)
    {
        if (tstamps[id]->istab())
        {
            TeventDummyTabTabed * evt = new TeventDummyTabTabed();
            evt->x = tstamps[id]->x;
            evt->y = tstamps[id]->y;
            events.push_back(evt);
        }
    }
};

template <class Base>
class CanDummyTab : public  Base
{
public:
    //Interface redefined by ofApp
    virtual void tab(float x, float y) {}

    //processing events callbacks
    TEventHandler(TeventDummyTabTabed)
    {
        TeventDummyTabTabed * e = static_cast<TeventDummyTabTabed *>(evt);
        tab(e->x,e->y);
    }

    //registering
    CanDummyTab()
    {
        TRegistraCallback(CanDummyTab,TeventDummyTabTabed);
        registerMeToInputGestureManager(Singleton<InputGestureDummyTab>::get());
    }

    //allways needed
    eventprocessorsType & getEP()
    {
        return Base::getEP();
    }
};

}
#endif // INPUTGESTUREDUMMYCLICK_H_INCLUDED
