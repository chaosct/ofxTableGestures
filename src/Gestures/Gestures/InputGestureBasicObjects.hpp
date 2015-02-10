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

#include <map>
#include <set>
#include "InputGestureTuio1.1.hpp"

struct commonObjectArgs : public commonIdArgs{
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

class InputGestureBasicObjects : public EventClient{
    public:
        typedef commonObjectArgs addTuioObjectArgs;
        typedef commonObjectArgs updateTuioObjectArgs;
        typedef commonIdArgs removeTuioObjectArgs;
        typedef commonIdArgs exitTuioObjectArgs;
        typedef commonObjectArgs enterTuioObjectArgs;

        static ofEvent<removeTuioObjectArgs> removeTuioObject;
        static ofEvent<exitTuioObjectArgs> exitTuioObject;
        static ofEvent<addTuioObjectArgs> addTuioObject;
        static ofEvent<enterTuioObjectArgs> enterTuioObject;
        static ofEvent<updateTuioObjectArgs> updateTuioObject;

        InputGestureBasicObjects();
        void addTuioObject2D(int id, int f_id,
                            float xpos, float ypos, float angle,
                            float xspeed, float yspeed, float rspeed,
                            float maccel, float raccel);
        void updateTuioObject2D(int id, int f_id,
                            float xpos, float ypos, float angle,
                            float xspeed, float yspeed, float rspeed,
                            float maccel, float raccel);
        void removeTuioObject2D(int id);
        void addTuioObject2D(InputGestureTuio112D::addTuioObject2DArgs & eventargs)
        {
            addTuioObject2D(eventargs.id, eventargs.f_id,
                            eventargs.xpos, eventargs.ypos, eventargs.angle,
                            eventargs.xspeed, eventargs.yspeed, eventargs.rspeed,
                            eventargs.maccel, eventargs.raccel);
        }
        void updateTuioObject2D(InputGestureTuio112D::updateTuioObject2DArgs & eventargs)
        {
            updateTuioObject2D(eventargs.id, eventargs.f_id,
                                eventargs.xpos, eventargs.ypos, eventargs.angle,
                                eventargs.xspeed, eventargs.yspeed, eventargs.rspeed,
                                eventargs.maccel, eventargs.raccel);
        }
        void removeTuioObject2D(InputGestureTuio112D::removeTuioObject2DArgs & eventargs)
        {
            removeTuioObject2D(eventargs.id);
        }

    private:
        std::map<int, const Graphic* > graphic_assignations;
        std::set<int> ids;
};

#endif

