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
        int r,g,b;
        int shapeid;
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

#endif // SHAPES_H_INCLUDED
