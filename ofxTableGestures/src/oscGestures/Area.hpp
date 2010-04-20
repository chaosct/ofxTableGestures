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

#endif // AREA_HPP_INCLUDED
