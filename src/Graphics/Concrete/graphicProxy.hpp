#ifndef _GRAPHICPROXY_HPP_
#define _GRAPHICPROXY_HPP_

#include "Graphic.hpp"

class graphicProxy : public Graphic{
    public:
        void setServer(Graphic* graphicServer){
            server = graphicServer;
        }

        void draw(){
            if (server != NULL){
                server->draw();
            }
        }

        bool collide(const ofPoint& point){
            if (server != NULL){
                return server->collide(point);
            }else{
                return false;
            }
        }

        void clear(){
            if (server != NULL){
                server->clear();
            }
        }

    private:
        Graphic* server;
};

#endif // _GRAPHICPROXY_HPP_
