#ifndef INPUTGESTUREDUMMYCLICK_H_INCLUDED
#define INPUTGESTUREDUMMYCLICK_H_INCLUDED

#include "InputGestureBasicFingers.h"
#include "TEvent.h"
#include <map>

namespace tuio
{

class clickcursor
{
    public:
    float tstamp;
    float x,y;
    float maxx, maxy, minx, miny;
    clickcursor(float _x,float _y,float t):tstamp(t),x(_x),y(_y),maxx(x),maxy(y),minx(x),miny(y){}
    void update(float _x,float _y)
    {
        maxx = max(maxx,_x);
        maxy = max(maxy,_y);
        minx = min(minx,_x);
        miny = min(miny,_y);
    }
    bool isclick()
    {
        float now = ofGetElapsedTimef();
        float dt = now - tstamp;
        if (dt > 0.2) return false;
        if (max(maxx-minx,maxy-miny) > 0.01) return false;
        return true;
    }
};

class TeventDummyClickClicked : public TTEvent <TeventDummyClickClicked>
{
public:
    float duration;
    float x,y;
};

class InputGestureDummyClick : public CanBasicFingers < tuioApp <InputGesture> >
{
    std::map<int32,clickcursor *> tstamps;
    InputGestureBasicFingers * basicfingers;
public:
    InputGestureDummyClick()
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
        tstamps[id] = new clickcursor(xpos,ypos,ofGetElapsedTimef());
    }
    void updateTuioCursor(int32 id, float xpos,float ypos,float xspeed,float yspeed,float maccel)
    {
        tstamps[id]->update(xpos,ypos);
    }
    void removeTuioCursor(int32 id)
    {
        if (tstamps[id]->isclick())
        {
            TeventDummyClickClicked * evt = new TeventDummyClickClicked();
            evt->x = tstamps[id]->x;
            evt->y = tstamps[id]->y;
            events.push_back(evt);
        }
    }
};

template <class Base>
class CanDummyClick : public  Base
{
public:
    //Interface redefined by ofApp
    virtual void click(float x, float y) {}

    //processing events callbacks
    TEventHandler(TeventDummyClickClicked)
    {
        TeventDummyClickClicked * e = static_cast<TeventDummyClickClicked *>(evt);
        click(e->x,e->y);
    }

    //registering
    CanDummyClick()
    {
        TRegistraCallback(CanDummyClick,TeventDummyClickClicked);
        registerMeToInputGestureManager(Singleton<InputGestureDummyClick>::get());
    }

    //allways needed
    eventprocessorsType & getEP()
    {
        return Base::getEP();
    }
};

}
#endif // INPUTGESTUREDUMMYCLICK_H_INCLUDED
