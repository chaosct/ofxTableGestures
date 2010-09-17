#ifndef AREA_HPP_INCLUDED
#define AREA_HPP_INCLUDED

class Area
{
    public:
    virtual bool isInside(float x, float y){}
};

class NoArea: public Area
{
    private:
    NoArea(){}
    public:
    bool isInside(float x, float y){return true;}
    static Area * Create()
    {
        static NoArea a;
        return &a;
    }
};

class ZeroArea: public Area
{
    private:
    ZeroArea(){}
    public:
    bool isInside(float x, float y){return false;}
    static Area * Create()
    {
        static ZeroArea a;
        return &a;
    }
};

class CircularArea: public Area
{
    public:
    float x,y,r;
    bool isInside(float X, float Y)
    {
        float dx = X-x;
        float dy = Y-y;
        return ((dx*dx+dy*dy) <= (r*r));
    }
};

class RoundTableArea: public Area
{
    public:
    static Area * Create()
    {
        static CircularArea a;
        a.x = 0.5f;
        a.y = 0.5f;
        a.r = 0.5f;
        return &a;
    }
};

#endif // AREA_HPP_INCLUDED
