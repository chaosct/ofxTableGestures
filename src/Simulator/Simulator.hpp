/*

    ofxTableGestures (formerly OF-TangibleFramework)
    Developed for Taller de Sistemes Interactius I
    Universitat Pompeu Fabra

    Copyright (c) 2010 Daniel Gallardo Grassot <daniel.gallardo@upf.edu>

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

#ifndef _SIMULATOR
#define _SIMULATOR

#include "ofMain.h"
#include "container.hpp"
#include <vector>

#include "ofxOscSender.h"
#include "ofxOscMessage.h"
#include "ofxOscBundle.h"
#define DEFAULT_PORT 3333
#define DEFAULT_ADDR "127.0.0.1"

namespace simulator{
    typedef std::vector<cursor*> cursor_list;
    typedef std::vector<object*> object_list;
    typedef std::list<string> message_queue;
    class Simulator{
        private:
            cursor_list cursors;
            object_list objects;
            cursor_list cursors_escene;
            object_list objects_escene;
            unsigned int sessionGenerator;
            unsigned int fseqGenerator;
            bool hold;
            bool select;
            bool move_selecteds;
            void SortObject(object* o);
            int ytray;
            int previous_y;
            float previous_timef;
            message_queue notify;
            ofTrueTypeFont	verdana;
            #ifdef _ofxOscSENDER_H
                ofxOscSender* sender;
                int port;
                std::string address;
                bool loaded;
                bool load_default;
            #endif
            string message_notif;
        public:
            Simulator();
            ~Simulator();
            void Draw();
            void Update();
            void Hold(bool stat);
            void Select(bool stat);
            void Reset();
            void mouseDragged(int x, int y, int button);
            void mousePressed(int x, int y, int button);
            void mouseReleased(int x, int y, int button);
            void windowResized(int w, int h);
        protected:
            container* Collide(int x,int y,bool only_objects=false);
            bool IsOnTheScene(container*c);
            bool IsAtLateralTray(container* c);
            bool IsAtBottomTray(container* c);
            cursor_list::iterator IsAtCursorList(cursor* c);
            object_list::iterator IsAtObjectList(object* o);
            void MoveYTray(int step);
            void cursorUpdated(cursor* c);
            void cursorDeleted(cursor* c);
            void objectUpdated(object* o);
            void objectRemoved(object* o);

            void addTuioObject(object* o);
            void updateTuioObject(object* o);
            void removeTuioObject(object* o);
            void addTuioCursor(cursor* c);
            void updateTuioCursor(cursor* c);
            void removeTuioCursor(cursor* c);

            void updateCursors();
            void updateObjects();

            float Transformx(float to_transform);
            float Transformy(float to_transform);

            bool LoadConfigFile(std::string path);

            void pushMessage(string message);
    };
}

#endif
