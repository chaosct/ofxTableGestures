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
    

*/

#ifndef _OBJECTFEEDBACK_H_
#define _OBJECTFEEDBACK_H_

#include <vector>
#include "InputGestureDirectObjects.hpp"

#define NAMEPATH "simulator.config"

namespace tableGraphics{
    class Polygon;
}

class ObjectFeedback{
    public:
        ObjectFeedback();
        ~ObjectFeedback();
        void newObject(InputGestureDirectObjects::newObjectArgs&);
        void removeObject(InputGestureDirectObjects::removeObjectArgs&);
        void update();
        void setGraphic(int id, tableGraphics::Polygon*);
        tableGraphics::Polygon* getGraphic(int fid);
        unsigned int getNumObjects();

    private:
        static const float squareSize;
        enum shapes{ SQUARE, CIRCLE, PENTAGON, DODECAHEDRON, STAR, SQUARE_ROUNDED };
        typedef shapes Shape; 
        struct colorShape{
            int id;
            Shape shape;
            ofColor color;
            colorShape(int _id = -1) : id(_id), shape(SQUARE), color(55, 55, 55){} // Default
            bool operator ==(const colorShape& rhs) const{
                return id == rhs.id;
            }
        };
        typedef colorShape colorShape;
        std::vector<colorShape> shapes;

        struct objectGraphic{
            DirectObject* object;
            tableGraphics::Polygon* graphic;
            bool toDelete;

            bool operator == (DirectObject* rhs) const{
                if (object == rhs){
                    return true;
                }else{
                    return false;
                }
            }

            bool operator == (int fid) const{
                if (object->f_id == fid){
                    return true;
                }else{
                    return false;
                }
            }
        };
        std::vector<objectGraphic> graphics;

        void loadGraphics();
};

#endif // _OBJECTFEEDBACK_H_

