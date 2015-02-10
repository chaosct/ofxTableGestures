#ifndef _AUTOGRAPHIC_HPP_
#define _AUTOGRAPHIC_HPP_

#include "graphicProxy.hpp"
#include "GraphicDispatcher.hpp" // Layer definitions

class autoGraphic : public Graphic{
    public:
        autoGraphic(int initLayer = APP_LAYER);
        virtual ~autoGraphic();

    private:
        graphicProxy* proxy;
        autoGraphic(const autoGraphic&);
        autoGraphic& operator=(const autoGraphic&);
};


template<int layer>
class autoLayerGraphic : public autoGraphic{
    public:
    autoLayerGraphic() : autoGraphic(layer) {}
};

typedef autoLayerGraphic<NOT_LAYER> NotificationGraphic;
typedef autoLayerGraphic<BGR_LAYER> BackgroundGraphic;
typedef autoLayerGraphic<BGR_LAYER+1> FeedbackGraphic;

#endif // _AUTOGRAPHIC_HPP_
