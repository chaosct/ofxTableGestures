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
        virtual float getX()const{return xpos;}
        virtual float getY()const{return ypos;}
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
        ///angle = atan2( y2-y1 / x2-x1 )
        float getAngle(const DirectPoint& point) const {
            float dx = point.getX() - getX();
            float dy = point.getY() - getY();
            float angle;
            ///for avoiding divide by 0, when dx = 0 the angle is M_PI/2
            if ( dx == 0 ) return M_PI/2;
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
