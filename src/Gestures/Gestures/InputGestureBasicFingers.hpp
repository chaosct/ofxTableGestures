/*

    ofxTableGestures (formerly OF-TangibleFramework)
    Developed for Taller de Sistemes Interactius I
    Universitat Pompeu Fabra

    Copyright (c) 2010 Carles F. Julià <carles.fernandez@upf.edu>

    Permission is hereby granted, free of charge, to any person
    obtaining a copy of this software and associated documentation
    files (the "Software"), to deal in the Software without
    restriction, including without limitation the rights to use,
    copy, modify, merge, publish, distribute, sublicense, and/or sell
    copies of the Software, and to permit persons to whom the
    Software is furnished to do so, subject to the following
    conditions:

    The above copyright notice and this permission notice shall be
    included in all copies or substantial portions of the Software.

    THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
    EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES
    OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
    NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT
    HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
    WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
    FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
    OTHER DEALINGS IN THE SOFTWARE.

*/

#ifndef TUIO_INPUTGESTUREBASICFINGERS_H
#define TUIO_INPUTGESTUREBASICFINGERS_H

#include <set>
#include "InputGestureTuio1.1.hpp"


class InputGestureBasicFingers : public  CanTuio112D<CompositeGesture>, public Singleton<InputGestureBasicFingers>
{
public:

    struct addTuioCursorArgs: public EventArgs
    {
        int id;
        float xpos;
        float ypos;
        float xspeed;
        float yspeed;
        float maccel;
    };
    struct updateTuioCursorArgs: public EventArgs
    {
        int id;
        float xpos;
        float ypos;
        float xspeed;
        float yspeed;
        float maccel;
    };
    struct removeTuioCursorArgs: public EventArgs
    {
        int id;
    };
    struct exitTuioCursorArgs: public EventArgs
    {
        int id;
    };
    struct enterTuioCursorArgs: public EventArgs
    {
        int id;
        float xpos;
        float ypos;
        float xspeed;
        float yspeed;
        float maccel;
    };

    ofEvent<removeTuioCursorArgs> removeTuioCursor;
    ofEvent<exitTuioCursorArgs> exitTuioCursor;
    ofEvent<addTuioCursorArgs> addTuioCursor;
    ofEvent<enterTuioCursorArgs> enterTuioCursor;
    ofEvent<updateTuioCursorArgs> updateTuioCursor;

    std::set<int> ids;


    InputGestureBasicFingers() {}
    void addTuioCursor2D(int id, float xpos,float ypos,float xspeed,float yspeed,float maccel)
    {
        ///TODO: treballar amb àrees
        //if(area->isInside(xpos,ypos))
        {
            ids.insert(id);
            addTuioCursorArgs eventargs;
            eventargs.id = id;
            eventargs.xpos = xpos;
            eventargs.ypos = ypos;
            eventargs.xspeed = xspeed;
            eventargs.yspeed = yspeed;
            eventargs.maccel = maccel;
            ofNotifyEvent(addTuioCursor,eventargs);

        }
    }
    void updateTuioCursor2D(int id, float xpos,float ypos,float xspeed,float yspeed,float maccel)
    {
        ///TODO: treballar amb àrees
        if(true /*area->isInside(xpos,ypos)*/)
        {
            if(ids.find(id) == ids.end())
            {
                ids.insert(id);
                enterTuioCursorArgs eventargs;
                eventargs.id = id;
                eventargs.xpos = xpos;
                eventargs.ypos = ypos;
                eventargs.xspeed = xspeed;
                eventargs.yspeed = yspeed;
                eventargs.maccel = maccel;
                ofNotifyEvent(enterTuioCursor,eventargs);

            }
            else
            {
                updateTuioCursorArgs eventargs;
                eventargs.id = id;
                eventargs.xpos = xpos;
                eventargs.ypos = ypos;
                eventargs.xspeed = xspeed;
                eventargs.yspeed = yspeed;
                eventargs.maccel = maccel;
                ofNotifyEvent(updateTuioCursor,eventargs);

            }
        }
        else
        {
            if(ids.find(id) != ids.end())
            {
                ids.erase(id);
                exitTuioCursorArgs eventargs;
                eventargs.id = id;
                ofNotifyEvent(exitTuioCursor,eventargs);

            }
        }
    }
    void removeTuioCursor2D(int id)
    {
        if(ids.find(id) != ids.end())
        {
            ids.erase(id);
            removeTuioCursorArgs eventargs;
            eventargs.id = id;
            ofNotifyEvent(removeTuioCursor,eventargs);

        }
    }

};


template <class Base>
class CanBasicFingers : public Base
{

public:
    void EaddTuioCursor(InputGestureBasicFingers::addTuioCursorArgs & eventargs)
    {
        addTuioCursor(eventargs.id,eventargs.xpos,eventargs.ypos,eventargs.xspeed,eventargs.yspeed,eventargs.maccel);
    }
    virtual void addTuioCursor(int id, float xpos,float ypos,float xspeed,float yspeed,float maccel) {}
    void EupdateTuioCursor(InputGestureBasicFingers::updateTuioCursorArgs & eventargs)
    {
        updateTuioCursor(eventargs.id,eventargs.xpos,eventargs.ypos,eventargs.xspeed,eventargs.yspeed,eventargs.maccel);
    }
    virtual void updateTuioCursor(int id, float xpos,float ypos,float xspeed,float yspeed,float maccel) {}
    void EremoveTuioCursor(InputGestureBasicFingers::removeTuioCursorArgs & eventargs)
    {
        removeTuioCursor(eventargs.id);
    }
    virtual void removeTuioCursor(int id) {}
    void EexitTuioCursor(InputGestureBasicFingers::exitTuioCursorArgs & eventargs)
    {
        exitTuioCursor(eventargs.id);
    }
    virtual void exitTuioCursor(int id)
    {
        removeTuioCursor(id);
    }
    void EenterTuioCursor(InputGestureBasicFingers::enterTuioCursorArgs & eventargs)
    {
        enterTuioCursor(eventargs.id,eventargs.xpos,eventargs.ypos,eventargs.xspeed,eventargs.yspeed,eventargs.maccel);
    }
    virtual void enterTuioCursor(int id, float xpos,float ypos,float xspeed,float yspeed,float maccel)
    {
        addTuioCursor(id,xpos,ypos,xspeed,yspeed,maccel);
    }
//    //Interface redefined by ofApp
//    virtual void addTuioCursor(int id, float xpos,float ypos,float xspeed,float yspeed,float maccel){}
//    virtual void updateTuioCursor(int id, float xpos,float ypos,float xspeed,float yspeed,float maccel){}
//    virtual void removeTuioCursor(int id){}
//    //Area-aware interface optionally redefined by ofApp
//    virtual void exitTuioCursor(int id)                                                                   {removeTuioCursor(id);}
//    virtual void enterTuioCursor(int id, float xpos,float ypos,float xspeed,float yspeed,float maccel)    {addTuioCursor(id,xpos,ypos,xspeed,yspeed,maccel);}

    //registering
    CanBasicFingers()
    {

        ofAddListener(InputGestureBasicFingers::Instance().addTuioCursor,this,&CanBasicFingers::EaddTuioCursor);
        ofAddListener(InputGestureBasicFingers::Instance().enterTuioCursor,this,&CanBasicFingers::EenterTuioCursor);
        ofAddListener(InputGestureBasicFingers::Instance().updateTuioCursor,this,&CanBasicFingers::EupdateTuioCursor);
        ofAddListener(InputGestureBasicFingers::Instance().removeTuioCursor,this,&CanBasicFingers::EremoveTuioCursor);
        ofAddListener(InputGestureBasicFingers::Instance().exitTuioCursor,this,&CanBasicFingers::EexitTuioCursor);

    }
    virtual ~CanBasicFingers()
    {

        ofRemoveListener(InputGestureBasicFingers::Instance().addTuioCursor,this,&CanBasicFingers::EaddTuioCursor);
        ofRemoveListener(InputGestureBasicFingers::Instance().enterTuioCursor,this,&CanBasicFingers::EenterTuioCursor);
        ofRemoveListener(InputGestureBasicFingers::Instance().updateTuioCursor,this,&CanBasicFingers::EupdateTuioCursor);
        ofRemoveListener(InputGestureBasicFingers::Instance().removeTuioCursor,this,&CanBasicFingers::EremoveTuioCursor);
        ofRemoveListener(InputGestureBasicFingers::Instance().exitTuioCursor,this,&CanBasicFingers::EexitTuioCursor);

    }

};


#endif
