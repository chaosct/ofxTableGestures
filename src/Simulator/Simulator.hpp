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

#include "OnlySimulator.h"


#include "ofxOscSender.h"
#include "ofxOscMessage.h"
#include "ofxOscBundle.h"
#define DEFAULT_PORT 3333
#define DEFAULT_ADDR "127.0.0.1"

namespace tableGraphics{
    class Polygon;
    class Text;
}

namespace simulator{
    typedef std::vector<Cursor*> cursor_list;
    typedef std::vector<Object*> object_list;
    typedef std::list<string> message_queue;
    class Simulator{
        public:
            Simulator();
            ~Simulator();
            void run(bool);
            bool isRunning();
            void Update();
            void Hold(bool stat);
            void Select(bool stat);
            void Reset();
            void mouseDragged(float x, float y, int button);
            void mousePressed(float x, float y, int button);
            void mouseReleased(float x, float y, int button);

        protected:
            Container* Collide(float x, float y, bool only_objects = false);
            bool IsOnTheScene(Container*c);
            bool IsAtLateralTray(Container* c);
            bool IsAtBottomTray(Container* c);
            cursor_list::iterator IsAtCursorList(Cursor* c);
            object_list::iterator IsAtObjectList(Object* o);
            void MoveYTray(int step);
            void SortObject(Object* o);
            Cursor* newCursor(ofVec2f);
            void cursorUpdated(Cursor* c);
            void cursorDeleted(Cursor* c);
            void objectUpdated(Object* o);
            void objectRemoved(Object* o);

            void addTuioObject(Object* o);
            void updateTuioObject(Object* o);
            void removeTuioObject(Object* o);
            void addTuioCursor(Cursor* c);
            void updateTuioCursor(Cursor* c);
            void removeTuioCursor(Cursor* c);

            void updateCursors();
            void updateObjects();

            float Transformx(float to_transform);
            float Transformy(float to_transform);

            bool LoadConfigFile(std::string path);
            void loadObjects();

            void pushMessage(string message);

        private:
            tableGraphics::Polygon* tray;
            tableGraphics::Text* simLog;
            cursor_list cursors;
            object_list objects;
            cursor_list cursors_escene;
            object_list objects_escene;
            unsigned int sessionGenerator;
            unsigned int fseqGenerator;
            bool hold;
            bool select;
            int ytray;
            float previous_y;
            float previous_timef;
            message_queue notify;
            ofTrueTypeFont      verdana;
            ofxOscSender* sender;
            std::string namepath;
            int port;
            std::string address;
            bool loaded;
            string message_notif;
            bool running;
    };
}

#endif
