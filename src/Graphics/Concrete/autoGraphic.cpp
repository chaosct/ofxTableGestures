#include "autoGraphic.hpp"
#include "GenericManager.hpp"
#include "GraphicDispatcher.hpp"

autoGraphic::autoGraphic(int initLayer){
    GenericManager::get<GraphicDispatcher>()->createGraphic(proxy, initLayer);
    proxy->setServer(this);
    proxy->setCollide(true);
}

autoGraphic::~autoGraphic(){
    proxy->setServer(NULL);
    GenericManager::get<GraphicDispatcher>()->removeGraphic(proxy);
}

