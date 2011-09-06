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

#ifndef _GRAPHICDISPATCHER
#define _GRAPHICDISPATCHER
#include <set>
#include "Singleton.hpp"
#include "Graphic.hpp"


class GraphicDispatcher : public Singleton<GraphicDispatcher>{
    private:
        typedef std::set<Graphic*,CompareLayers> GraphicsList;
        GraphicsList graphics;
        std::list<Graphic*> to_delete;
        unsigned long ngraphics;
    protected:
        friend class Singleton<GraphicDispatcher>;
        GraphicDispatcher();
        friend class Graphic;
        void bring_top(Graphic* graphic);
    public:
        ~GraphicDispatcher();
        void Draw();
        void Update();
        void Resize(int w, int h);
        void AddGraphic(Graphic* graphic);
        void RemoveGraphic(Graphic* graphic);
        void SafeDeleteGraphic(Graphic* graphic);
        Graphic * Collide(ofPoint const & point);
};

#endif //_GRAPHICDISPATCHER
