#include "GraphicDispatcher.hpp"

GraphicDispatcher* GraphicDispatcher::pinstance=NULL;

GraphicDispatcher::GraphicDispatcher(){
}

GraphicDispatcher::~GraphicDispatcher(){
}

GraphicDispatcher& GraphicDispatcher::Instance(){
    if(pinstance == NULL)
        pinstance = new GraphicDispatcher();
    return *pinstance;
}

void GraphicDispatcher::Draw(){
    for(std::list<Graphic*>::iterator it = graphics.begin(); it != graphics.end(); it++)
        (*it)->draw();
}

void GraphicDispatcher::Update(){
    for(std::list<Graphic*>::iterator it = graphics.begin(); it != graphics.end(); it++)
        (*it)->update();
}

void GraphicDispatcher::Resize(int w, int h){
    for(std::list<Graphic*>::iterator it = graphics.begin(); it != graphics.end(); it++)
        (*it)->resize(w,h);
}

void GraphicDispatcher::AddGraphic(Graphic* graphic){
    graphics.push_back(graphic);
}

void GraphicDispatcher::RemoveGraphic(Graphic* graphic){
    graphics.remove(graphic);
}
