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

class GraphicSmartContainer
{
    friend class Graphic;
    public:
    Graphic * graphic;
    unsigned long created_time;
    GraphicSmartContainer(Graphic * gr):graphic(gr){}
    void unregister(){graphic=NULL;}
    bool todelete(){return graphic == NULL;}
    int GetLayer()
    {
        if(todelete()) return 0;
        return graphic->GetLayer();
    }
    void draw()
    {
        if(!todelete()) graphic->draw();
    }
    void update()
    {
        if(!todelete()) graphic->update();
    }
    void resize(int w, int h)
    {
        if(!todelete()) graphic->resize(w,h);
    }
    bool Collide(ofPoint const & point)
    {
        if(todelete()) return false;
        return graphic->Collide(point);
    }
};

struct CompareLayers
{
    inline bool operator()(GraphicSmartContainer* object1, GraphicSmartContainer* object2)
    {
        if (object1->GetLayer() == object2->GetLayer())
            return (object1->created_time < object2->created_time);
        return (object1->GetLayer() > object2->GetLayer());
    }
};

class GraphicDispatcher : public Singleton<GraphicDispatcher>{
    private:
        typedef std::set<GraphicSmartContainer*,CompareLayers> GraphicsList;
        GraphicsList graphics;
        //std::list<Graphic*> to_delete;
        unsigned long ngraphics;
    protected:
        friend class Singleton<GraphicDispatcher>;
        GraphicDispatcher();
        friend class Graphic;
        void bring_top(GraphicSmartContainer* graphic);
        void ChangeLayer(GraphicSmartContainer * graphic, int newlayer);
    public:
        ~GraphicDispatcher();
        void Draw();
        void Update();
        void Resize(int w, int h);
        void AddGraphic(GraphicSmartContainer* graphic);
        //void RemoveGraphic(Graphic* graphic);
        //void SafeDeleteGraphic(Graphic* graphic);
        Graphic * Collide(ofPoint const & point);
};

#endif //_GRAPHICDISPATCHER
