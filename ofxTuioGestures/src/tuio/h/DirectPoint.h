#ifndef DIRECTPOINT_H_INCLUDED
#define DIRECTPOINT_H_INCLUDED

#include <math.h>

class DirectPoint{
    public:
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
        float getX(){return xpos;}
        float getY(){return ypos;}
        ///getDistance-returns the distance between this and point
        ///d = sqrt( (x2-x1)^2 + (y2-y1)^2 )
        float getDistance(const DirectPoint& point){
            float dx = point.xpos -xpos;
            float dy = point.ypos -ypos;
            return sqrt( dx*dx + dy*dy);
        }
        ///getAngle-reurns the angle between this and point
        ///angle = atan( |y2-y1| / |x2-x1| )
        float getAngle(const DirectPoint& point){
            float dy = point.ypos-ypos;
            float dx = point.xpos-xpos;
            float angle;
            ///for avoiding divide by 0, when dx = 0 the angle is M_PI/2
            if ( dx == 0 ) angle = M_PI/2;
            ///calculates the angle
            else angle= atan(fabs(dy)/fabs(dx));
            ///sets the right quadrant
            if ( dy >= 0 && dx >= 0)return angle;
            else if ( dy >= 0 && dx < 0 )return M_PI-angle;
            else if ( dy < 0 && dx <= 0 )return M_PI+angle;
            else if ( dy < 0 && dx > 0 )return (2*M_PI)-angle;
            return angle;
        }
    /// Setters
        void setX(float x){xpos = x;}
        void setY(float y){ypos = y;}
        void set(float x, float y){setX(x); setY(y);}
    /// operators
        DirectPoint& operator=(const DirectPoint& point){
            if(this == & point)return *this;
            xpos = point.xpos;
            ypos = point.ypos;
            return *this;
        }
        DirectPoint& operator+=(const DirectPoint& point){
            xpos += point.xpos;
            ypos += point.ypos;
            return *this;
        }
        DirectPoint& operator-=(const DirectPoint& point){
            xpos -= point.xpos;
            ypos -= point.ypos;
            return *this;
        }
        DirectPoint& operator*=(float mult){
            xpos = xpos*mult;
            ypos = ypos*mult;
            return *this;
        }
        DirectPoint& operator/=(float div){
            xpos = xpos*div;
            ypos = ypos*div;
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
