/*

    OF-TangibleFramework . Framework for Taller de Sistemes Interactius I
    Universitat Pompeu Fabra

    Copyright (c) 2009 Daniel Gallardo Grassot <daniel.gallardo@upf.edu>

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

#ifndef SHAPE_H_INCLUDED
#define SHAPE_H_INCLUDED

#include "ofMain.h"
#include "container.hpp"
#include <map>
#include <list>

#define SQUARE          0
#define CIRCLE          1
#define PENTAGON        2
#define DODECAHEDRON    3
#define STAR            4
#define ROUNDSQUARE     5

namespace shapes
{

class Shape{
    public:
        virtual void  draw()=0;
};

class shapeSquare:public Shape{
    bool round_edges;
    void Edge(float radius, int side, float x_offset, float y_offset,  float h_x_offset, float h_y_offset);
    public:
        shapeSquare(bool round_edges = false);
        virtual void draw();
};

class shapeCircle:public Shape{
    public:
        virtual void draw();
};

class shapeStar:public Shape{
    public:
        virtual void draw();
};

class shapeDodecahedron:public Shape{
  public:
        virtual void draw();
};

class shapePentagon:public Shape{
  public:
        virtual void draw();
};

class shape_color{
    public:
        shape_color(int _shapeid, int _r, int _g, int _b);
        int shapeid;
        int r,g,b;
        void draw(bool draw_color = true);
};

class Figure_shape{
    private:
        friend class object;
        std::map<int, shape_color*> objectid_shape;
        void Load();
        static Figure_shape* pinstance;
        Figure_shape();
    public:
        static Figure_shape& Instance();
        ~Figure_shape();
        shape_color* GetShape(int f_id);
        void drawShape(int f_id,bool add_color = true);
        std::list<int> GetFiducialIds();
};

}
#endif // SHAPES_H_INCLUDED
