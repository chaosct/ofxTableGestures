/*

    OF-TangibleFramework . Framework for Taller de Sistemes Interactius I
    Universitat Pompeu Fabra

    Copyright (c) 2010 Daniel Gallardo <daniel.gallardo@upf.edu>
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
#ifndef DIRECTPOINT_H_INCLUDED
#define DIRECTPOINT_H_INCLUDED

#include <cmath>

class DirectPoint{
    protected:
    //[this should be protected but are used at demos as public] protected:
        float xpos, ypos;
    public:
    /// empty constructor initializase point to (0,0)
        DirectPoint():xpos(0),ypos(0){}
    /// initializase point to (x,y)
        DirectPoint(float x, float y):xpos(x),ypos(y){}
    /// copy constructor
        DirectPoint(const DirectPoint& point):xpos(point.xpos),ypos(point.ypos){}
    /// Getters
        float getX()const{return xpos;}
        float getY()const{return ypos;}
        ///getDistance-returns the distance between this and point
        ///d = sqrt( (x2-x1)^2 + (y2-y1)^2 )
        float getDistance(const DirectPoint& point){
            float dx = point.getX() - getX();
            float dy = point.getY() - getY();
            return sqrt( dx*dx + dy*dy);
        }
        float getDistance(const DirectPoint * point){return getDistance(*point);}
        float getDistance(float x, float y){
            float dx = x -getX();
            float dy = y -getY();
            return sqrt( dx*dx + dy*dy);
        }
        ///getAngle-reurns the angle between this and point
        float getAngle(const DirectPoint& point) const {
            float dx = point.getX() - getX();
            float dy = point.getY() - getY();
            return atan2(dy,dx);
        }
        float getAngle(const DirectPoint* point){
            return getAngle(*point);
        }
    /// Setters
        void setX(float x){xpos = x;}
        void setY(float y){ypos = y;}
        void set(float x, float y){setX(x); setY(y);}
    /// operators
        bool operator==(const DirectPoint& point){
            return (getX()==point.getX())&&(getY()==point.getY());
        }
        bool operator!=(const DirectPoint& point){
            return !(*this == point);
        }
        DirectPoint& operator=(const DirectPoint& point){
            if(this == & point)return *this;
            setX(point.getX());
            setY(point.getY());
            return *this;
        }
        DirectPoint& operator+=(const DirectPoint& point){
            setX(getX()+point.getX());
            setY(getY()+point.getY());
            return *this;
        }
        DirectPoint& operator-=(const DirectPoint& point){
            setX(getX()-point.getX());
            setY(getY()-point.getY());
            return *this;
        }
        DirectPoint& operator*=(float mult){
            setX(getX()*mult);
            setY(getY()*mult);
            return *this;
        }
        DirectPoint& operator/=(float div){
            setX(getX()/div);
            setY(getY()/div);
            return *this;
        }
        const DirectPoint& operator+(const DirectPoint& point)const{
            return DirectPoint(*this) += point;
        }
        const DirectPoint& operator-(const DirectPoint& point)const{
            return DirectPoint(*this) -= point;
        }
        const DirectPoint& operator*(float mult)const{
            return DirectPoint(*this) *= mult;
        }
        const DirectPoint& operator/(float div)const{
            return DirectPoint(*this) /= div;
        }
};

#endif // DIRECTPOINT_H_INCLUDED
