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

#ifndef TUIO_INPUTGESTUREBASICOBJECTS_H
#define TUIO_INPUTGESTUREBASICOBJECTS_H

#include <set>

#include "InputGestureTuio1.1.hpp"




class InputGestureBasicObjects : public CanTuio112D < CompositeGesture >, public Singleton<InputGestureBasicObjects>
{
    std::set<int> ids;
public:
    struct addTuioObjectArgs: public EventArgs
    {
        int id;
        int f_id ;
        float xpos;
        float ypos;
        float angle;
        float xspeed;
        float yspeed;
        float rspeed;
        float maccel;
        float raccel;
    };
    struct updateTuioObjectArgs: public EventArgs
    {
        int id;
        int f_id ;
        float xpos;
        float ypos;
        float angle;
        float xspeed;
        float yspeed;
        float rspeed;
        float maccel;
        float raccel;
    };
    struct removeTuioObjectArgs: public EventArgs
    {
        int id;
    };
    struct enterTuioObjectArgs: public EventArgs
    {
        int id;
        int f_id ;
        float xpos;
        float ypos;
        float angle;
        float xspeed;
        float yspeed;
        float rspeed;
        float maccel;
        float raccel;
    };
    struct exitTuioObjectArgs: public EventArgs
    {
        int id;
    };
    ofEvent<removeTuioObjectArgs> removeTuioObject;
    ofEvent<addTuioObjectArgs> addTuioObject;
    ofEvent<updateTuioObjectArgs> updateTuioObject;
    ofEvent<exitTuioObjectArgs> exitTuioObject;
    ofEvent<enterTuioObjectArgs> enterTuioObject;


    InputGestureBasicObjects() {}
    void addTuioObject2D(int id, int f_id ,float xpos,float ypos, float angle, float xspeed,float yspeed,float rspeed,float maccel, float raccel)
    {
        ///TODO areas
        //if(area->isInside(xpos,ypos))
        {
            ids.insert(id);
            addTuioObjectArgs eventargs;
            eventargs.id = id;
            eventargs. f_id  =  f_id ;
            eventargs. xpos =  xpos;
            eventargs. ypos =  ypos;
            eventargs.  angle =   angle;
            eventargs.  xspeed =   xspeed;
            eventargs. yspeed =  yspeed;
            eventargs. rspeed =  rspeed;
            eventargs. maccel =  maccel;
            eventargs.  raccel =   raccel;
            ofNotifyEvent(addTuioObject,eventargs);

        }
    }
    void updateTuioObject2D(int id, int f_id ,float xpos,float ypos, float angle, float xspeed,float yspeed,float rspeed,float maccel, float raccel)
    {
        ///TODO areas
        if( true /*area->isInside(xpos,ypos)*/)
        {
            if(ids.find(id) == ids.end())
            {
                ids.insert(id);
                enterTuioObjectArgs eventargs;
                eventargs.id = id;
                eventargs. f_id  =  f_id ;
                eventargs. xpos =  xpos;
                eventargs. ypos =  ypos;
                eventargs.  angle =   angle;
                eventargs.  xspeed =   xspeed;
                eventargs. yspeed =  yspeed;
                eventargs. rspeed =  rspeed;
                eventargs. maccel =  maccel;
                eventargs.  raccel =   raccel;
                ofNotifyEvent(enterTuioObject,eventargs);

            }
            else
            {
                updateTuioObjectArgs eventargs;
                eventargs.id = id;
                eventargs. f_id  =  f_id ;
                eventargs. xpos =  xpos;
                eventargs. ypos =  ypos;
                eventargs.  angle =   angle;
                eventargs.  xspeed =   xspeed;
                eventargs. yspeed =  yspeed;
                eventargs. rspeed =  rspeed;
                eventargs. maccel =  maccel;
                eventargs.  raccel =   raccel;
                ofNotifyEvent(updateTuioObject,eventargs);

            }
        }
        else
        {
            if(ids.find(id) != ids.end())
            {
                ids.erase(id);
                exitTuioObjectArgs eventargs;
                eventargs.id = id;
                ofNotifyEvent(exitTuioObject,eventargs);

            }
        }
    }
    void removeTuioObject2D(int id)
    {
        if(ids.find(id) != ids.end())
        {
            ids.erase(id);
            removeTuioObjectArgs eventargs;
            eventargs.id = id;
            ofNotifyEvent(removeTuioObject,eventargs);

        }
    }
};

template <class Base>
class CanBasicObjects : public Base
{
public:
    void EaddTuioObject(InputGestureBasicObjects::addTuioObjectArgs & eventargs)
    {
        addTuioObject(eventargs.id,eventargs.f_id,eventargs.xpos,eventargs.ypos,eventargs.angle,eventargs.xspeed,eventargs.yspeed,eventargs.rspeed,eventargs.maccel,eventargs.raccel);
    }
    virtual void addTuioObject(int id, int f_id ,float xpos,float ypos, float angle, float xspeed,float yspeed,float rspeed,float maccel, float raccel) {}
    void EupdateTuioObject(InputGestureBasicObjects::updateTuioObjectArgs & eventargs)
    {
        updateTuioObject(eventargs.id,eventargs.f_id,eventargs.xpos,eventargs.ypos,eventargs.angle,eventargs.xspeed,eventargs.yspeed,eventargs.rspeed,eventargs.maccel,eventargs.raccel);
    }
    virtual void updateTuioObject(int id, int f_id ,float xpos,float ypos, float angle, float xspeed,float yspeed,float rspeed,float maccel, float raccel) {}
    void EremoveTuioObject(InputGestureBasicObjects::removeTuioObjectArgs & eventargs)
    {
        removeTuioObject(eventargs.id);
    }
    virtual void removeTuioObject(int id) {}
    void EenterTuioObject(InputGestureBasicObjects::enterTuioObjectArgs & eventargs)
    {
        enterTuioObject(eventargs.id,eventargs.f_id,eventargs.xpos,eventargs.ypos,eventargs.angle,eventargs.xspeed,eventargs.yspeed,eventargs.rspeed,eventargs.maccel,eventargs.raccel);
    }
    virtual void enterTuioObject(int id, int f_id ,float xpos,float ypos, float angle, float xspeed,float yspeed,float rspeed,float maccel, float raccel)
    {
        addTuioObject(id, f_id , xpos, ypos, angle, xspeed, yspeed, rspeed, maccel, raccel);
    }
    void EexitTuioObject(InputGestureBasicObjects::exitTuioObjectArgs & eventargs)
    {
        exitTuioObject(eventargs.id);
    }
    virtual void exitTuioObject(int id)
    {
        removeTuioObject(id);
    }

    //registering
    CanBasicObjects()
    {
        ofAddListener(InputGestureBasicObjects::Instance().addTuioObject,this,&CanBasicObjects::EaddTuioObject);
        ofAddListener(InputGestureBasicObjects::Instance().updateTuioObject,this,&CanBasicObjects::EupdateTuioObject);
        ofAddListener(InputGestureBasicObjects::Instance().removeTuioObject,this,&CanBasicObjects::EremoveTuioObject);
        ofAddListener(InputGestureBasicObjects::Instance().enterTuioObject,this,&CanBasicObjects::EenterTuioObject);
        ofAddListener(InputGestureBasicObjects::Instance().exitTuioObject,this,&CanBasicObjects::EexitTuioObject);
    }

};

#endif
