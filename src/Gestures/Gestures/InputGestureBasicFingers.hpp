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

#include <map>
#include <set>
#include "InputGestureTuio1.1.hpp"

struct commonCursorArgs : public commonIdArgs{
    float xpos;
    float ypos;
    float xspeed;
    float yspeed;
    float maccel;
};

class InputGestureBasicFingers : public EventClient{
    public:
        typedef commonCursorArgs addTuioCursorArgs;
        typedef commonCursorArgs updateTuioCursorArgs;
        typedef commonIdArgs removeTuioCursorArgs;
        typedef commonIdArgs exitTuioCursorArgs;
        typedef commonCursorArgs enterTuioCursorArgs;

        static ofEvent<removeTuioCursorArgs> removeTuioCursor;
        static ofEvent<exitTuioCursorArgs> exitTuioCursor;
        static ofEvent<addTuioCursorArgs> addTuioCursor;
        static ofEvent<enterTuioCursorArgs> enterTuioCursor;
        static ofEvent<updateTuioCursorArgs> updateTuioCursor;

        InputGestureBasicFingers();
        void addTuioCursor2D(int id, float xpos,float ypos,float xspeed,float yspeed,float maccel);
        void updateTuioCursor2D(int id, float xpos,float ypos,float xspeed,float yspeed,float maccel);
        void removeTuioCursor2D(int id);
        void addTuioCursor2D(InputGestureTuio112D::addTuioCursor2DArgs & eventargs){
            addTuioCursor2D(eventargs.id,
                            eventargs.xpos, eventargs.ypos,
                            eventargs.xspeed, eventargs.yspeed,
                            eventargs.maccel);
        }
        void updateTuioCursor2D(InputGestureTuio112D::updateTuioCursor2DArgs & eventargs){
            updateTuioCursor2D(eventargs.id,
                                eventargs.xpos, eventargs.ypos,
                                eventargs.xspeed, eventargs.yspeed,
                                eventargs.maccel);
        }
        void removeTuioCursor2D(InputGestureTuio112D::removeTuioCursor2DArgs & eventargs){
            removeTuioCursor2D(eventargs.id);
        }

    private:
        std::map<int, const Graphic*> graphic_assignations;
        std::set<int> ids;
};
#endif

