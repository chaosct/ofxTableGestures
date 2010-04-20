#ifndef AREAGESTURE_HPP_INCLUDED
#define AREAGESTURE_HPP_INCLUDED

#include "InputGesture.hpp"
#include "tuioApp.hpp"

namespace tuio
{

class Area
{
    public:
    bool isInside(float x, float y){}
};

class InputGestureProxy: inputGestureManager, InputGesture
{
    public:
    void ProcessBundle( const osc::ReceivedBundle& b, const IpEndpointName& remoteEndpoint )
    {
        IGMProcessBundle( b, remoteEndpoint );
    }
};

class tuioArea : public tuioApp<>
{
    Area * area;
    InputGestureProxy *p;

    template<typename GestureType>
    static GestureType * getGestureByArea(Area * a)
    {
       static std::map<Area*, GestureType *> pairs;
       GestureType * ig;
       if(pairs.find(a) == pairs.end())
       {
           ig = new GestureType();
       }
       else
       {
           ig = pairs[a];
       }
       return ig;
    }

    public:

    void setArea(Area * a)
    {
        area = a;
    }

    tuioArea():tuioApp(),area(NULL)
    {
        p = new InputGestureProxy();
        inputGestureManager::Instance().addGesture(p);
    }

    void registerInputGesture(InputGesture * IG)
    {
        p->addGesture(IG);
        feeders.push_back(IG);
    }


    template< typename I>
    void registerIG()
    {
        I * ig = getGestureByArea<I>(area);
        registerInputGesture(ig);
    }
};


}

#endif // AREAGESTURE_HPP_INCLUDED
