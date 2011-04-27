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

#ifndef _GRAPHIC
#define _GRAPHIC


#define BGR_LAYER 200
#define APP_LAYER 100
#define NOT_LAYER 0

#include "Area.hpp"

#include "ofMain.h"

#include "EventClient.hpp"

class Graphic :public Area, public EventClient{
    public:
        Graphic();
        Graphic(int _layer);
        Graphic(Graphic & original);
        virtual ~Graphic();
        int GetLayer();
		void BringTop();
		virtual bool Collide(ofPoint const & point);
		virtual void Position(float & x, float & y);
    protected:
        int layer;
        friend class GraphicDispatcher;
        virtual void draw(){}
        virtual void update(){}
        virtual void resize(int w, int h){}
};

template<int Layer>
class TGraphic: public Graphic
{
    public:
    TGraphic():Graphic(Layer){}
};

typedef TGraphic<NOT_LAYER> NotificationGraphic;
typedef TGraphic<BGR_LAYER> BackgroundGraphic;

bool CompareLayers(Graphic* object1, Graphic* object2);

//template<typename T>
//class OnTable: public T
//{
//    public:
//    OnTable()
//    {
//        this->Register(NULL);
//    }
//};

#endif //_GRAPHICDISPATCHER
