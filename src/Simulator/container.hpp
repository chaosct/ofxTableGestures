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

#ifndef _CONTAINER_HPP_
#define _CONTAINER_HPP_

#include "ofVec2f.h"

namespace tableGraphics{
    class Polygon;
    class Text;
    class Line;
}

#define CURSOR_RADIUS 0.01f
#define OBJECT_RADIUS 0.08f

namespace simulator{
    class Container{
        friend class Simulator;

        public:
            Container(unsigned int _sid,
                float _xpos, float _ypos,
                float _xspeed, float _yspeed,
                float _maccel);
            virtual ~Container();
            virtual bool Collide(float x, float y);
            virtual void Add(float x, float y, bool only = 0);
            virtual void Update(float x, float y, bool only = 0);
            virtual void updateGraphic() = 0;
            virtual void setVisible(bool);

        protected:
            unsigned int sid;
            ofVec2f position;
            ofVec2f speed;
            float maccel;
            bool mouse_on;
            tableGraphics::Polygon* graphic;

        private:
            ofVec2f previous_coords;
            float previous_time;
            float mspeed;
    };

    class Cursor : public Container{
        public:
            Cursor(unsigned int _sid,
                float _xpos, float _ypos,
                float _xspeed, float _yspeed,
                float _maccel);
            void updateGraphic();

            void hold(bool);
            bool isHolded();
            void select(bool);
            bool isSelected();

        private:
            bool holded;
            bool selected;
    };

    class Object : public Container{
        friend class Simulator;

        public:
            Object(unsigned int _sid,unsigned int _fid,
                float _xpos,float _ypos,float _angle,
                float _xspeed,float _yspeed,float _rspeed,
                float _maccel,float _raccel,
                int _trayNumber = 0,
                tableGraphics::Polygon* source = NULL);
            void AddAngle(bool only = false);
            void UpdateAngle(float _angle, bool only = false);
            void Add(float x, float y,bool only = false);
            void Update(float x, float y,bool only = false);
            void updateGraphic();
            void setVisible(bool);

        private:
            tableGraphics::Text* idNumber;
            tableGraphics::Line* angleLine;
            unsigned int fid;
            float angle;
            float rspeed;
            float raccel;
            int tray_number;
            bool isUp;

            float angle_old;
            float previous_angle_time;
            float rspeed_old;
    };
}

#endif // _CONTAINER_HPP_

