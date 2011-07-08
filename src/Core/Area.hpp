/*

    ofxTableGestures (formerly OF-TangibleFramework)
    Developed for Taller de Sistemes Interactius I
    Universitat Pompeu Fabra

    Copyright (c) 2010 Carles F. Julià <carles.fernandez@upf.edu>

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

#ifndef AREA_HPP_INCLUDED
#define AREA_HPP_INCLUDED

/*class Area
{
    public:
    virtual bool isInside(float x, float y){return false;}
};
*/

//class NoArea: public Area
//{
//    private:
//    NoArea(){}
//    public:
//    bool isInside(float x, float y){return true;}
//    static Area * Create()
//    {
//        static NoArea a;
//        return &a;
//    }
//};
//
//class ZeroArea: public Area
//{
//    private:
//    ZeroArea(){}
//    public:
//    bool isInside(float x, float y){return false;}
//    static Area * Create()
//    {
//        static ZeroArea a;
//        return &a;
//    }
//};
//
//class CircularArea: public Area
//{
//    public:
//    float x,y,r;
//    bool isInside(float X, float Y)
//    {
//        float dx = X-x;
//        float dy = Y-y;
//        return ((dx*dx+dy*dy) <= (r*r));
//    }
//};
//
//class RoundTableArea: public Area
//{
//    public:
//    static Area * Create()
//    {
//        static CircularArea a;
//        a.x = 0.5f;
//        a.y = 0.5f;
//        a.r = 0.5f;
//        return &a;
//    }
//};

#endif // AREA_HPP_INCLUDED
