/*

    TSIframework . Framework for Taller de Sistemes Interactius I
    Universitat Pompeu Fabra

    Copyright (c) 2010 Daniel Gallardo <daniel.gallardo@upf.edu>

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
#ifndef FIDUCIALGESTURES_HPP_INCLUDED
#define FIDUCIALGESTURES_HPP_INCLUDED

#include "InputGestureDirectFingers.hpp"
#include "InputGestureDirectObjects.hpp"

namespace tuio
{

SimpleDeclareEvent(CanFiducialGestures,TikUp,int,int);
SimpleDeclareEvent(CanFiducialGestures,TikDown,int, int);
SimpleDeclareEvent(CanFiducialGestures,Shake,int,int);

class time_point{
    public:
        time_point(float t, DirectPoint p):time(t),point(p){}
        float time;
        DirectPoint point;
};

class aux_fiducial_gesture{
    public:
        aux_fiducial_gesture():object(NULL),previous_fid_angle(0),previous_fid_angle_offset(0){}
        aux_fiducial_gesture(DirectObject * o):object(o),previous_fid_angle(o->angle),previous_fid_angle_offset(o->angle){
            points.push_back(time_point(ofGetElapsedTimef(),DirectPoint(o->getX(),o->getY())));
        }
        DirectObject * object;
        float previous_fid_angle;
        float previous_fid_angle_offset;

        std::list<time_point> points;
        void Update(float shake_time){
            if(points.size() != 0){
                bool end = false;
                std::list<time_point>::iterator it = points.begin();
                float actual_time = ofGetElapsedTimef();
                while (!end){
                    if( (actual_time-points.begin()->time) > shake_time)
                        points.pop_front();
                    else end = true;
                    if (points.size() == 0) end = true;
                }
            }
        }
        DirectPoint GetMidPoint(){
            DirectPoint p(0,0);
            int i = 0;
            for(std::list<time_point>::iterator it = points.begin(); it != points.end(); it++){
                i++;
                p+=(*it).point;
            }
            p = p/i;
            return p;
        }
        float GetMaxDistance(DirectPoint centre){
            float toreturn = 0;
            for(std::list<time_point>::iterator it = points.begin(); it != points.end(); it++){
                float local_dist = (centre.getDistance((*it).point));
                if(local_dist > toreturn)toreturn = local_dist;
            }
            return toreturn;
        }
};

class InputGestueFiducial : public CanDirectObjects < CompositeGesture >
{
    float & TikStep;
    float & Shake_time;
    float & Shake_threshold;
    float & Shake_radius;
    std::map < int, aux_fiducial_gesture > fiducials;

    public:
    InputGestueFiducial():
        TikStep(GlobalConfig::getRef("GESTURES:FIDUCIALGESTURES:TIKSTEP", (float)(M_PI/8.0f) )),
        Shake_time(GlobalConfig::getRef("GESTURES:FIDUCIALGESTURES:SHAKETIME", 2.0f )),
        Shake_threshold(GlobalConfig::getRef("GESTURES:FIDUCIALGESTURES:SHAKETHRESHOLD", 12.0f )),
        Shake_radius(GlobalConfig::getRef("GESTURES:FIDUCIALGESTURES:SHAKERADIUS", 0.02f )){}

    virtual void newObject(DirectObject * object){
        fiducials[object->s_id] = aux_fiducial_gesture(object);
    }

    virtual void updateObject(DirectObject * object){
        ///Check tikUP/DOWN
        fiducials[object->s_id].Update(Shake_time);
        float new_angle = object->angle;
        float angle_increment = new_angle - fiducials[object->s_id].previous_fid_angle;
        if( angle_increment > M_PI)  angle_increment = (new_angle - (2*M_PI))-fiducials[object->s_id].previous_fid_angle;
        if( angle_increment < -M_PI)  angle_increment = (new_angle + (2*M_PI))-fiducials[object->s_id].previous_fid_angle;
        if(fabs( angle_increment) >= TikStep){
            if( angle_increment >0){
                SimpleCallEvent(CanFiducialGestures,TikDown,(object->f_id,object->s_id));
            }else{
                SimpleCallEvent(CanFiducialGestures,TikUp,(object->f_id,object->s_id));
            }
            fiducials[object->s_id].previous_fid_angle = new_angle;
        }
        ///check if it is a deplacement
        angle_increment = new_angle-fiducials[object->s_id].previous_fid_angle_offset;
        if(fabs(angle_increment) <= 0.0001f) {
            fiducials[object->s_id].points.push_back(time_point(ofGetElapsedTimef(),DirectPoint(object->getX(),object->getY())));
        }
        fiducials[object->s_id].previous_fid_angle_offset = new_angle;
        ///CALCULATE SHAKE
        if(fiducials[object->s_id].points.size() > Shake_threshold ){
            DirectPoint p = fiducials[object->s_id].GetMidPoint();
            if(fiducials[object->s_id].GetMaxDistance(p) < Shake_radius){
                SimpleCallEvent(CanFiducialGestures,Shake,(object->f_id,object->s_id));
                fiducials[object->s_id].points.clear();
            }
        }
    }

    virtual void removeObject(DirectObject * object){
        fiducials.erase(object->s_id);
    }
};


template<class Base>
class CanFiducialGestures: public Base
{
    public:
    //Interface redefined by ofApp
    virtual void TikUp(int fid,int sid){}
    virtual void TikDown(int fid,int sid){}
    virtual void Shake(int fid,int sid){}

    void Register(Area * a)
    {
        Base::Register(a);
        SimpleRegisterEvent(CanFiducialGestures, TikUp);
        SimpleRegisterEvent(CanFiducialGestures, TikDown);
        SimpleRegisterEvent(CanFiducialGestures, Shake);
        Base::template registerIG<InputGestueFiducial>();
    }
};

}

#endif // FIDUCIALGESTURES_HPP_INCLUDED
