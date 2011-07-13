/*

    ofxTableGestures (formerly OF-TangibleFramework)
    Developed for Taller de Sistemes Interactius I
    Universitat Pompeu Fabra

    Copyright (c) 2011 Carles F. Julià <carles.fernandez@upf.edu>

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

#ifndef ALARM_HPP_INCLUDED
#define ALARM_HPP_INCLUDED

#include "Singleton.hpp"
#include "Graphic.hpp"

class Alarm
{
    class Alarm_detail: Graphic, public Singleton<Alarm_detail>
    {
        struct schedule
        {
            float time;
            Poco::AbstractDelegate<float> * delegate;
        };
        struct CompareSchedule
        {
            bool operator()(const schedule & s1, const schedule & s2)
            {
                if(s1.time == s2.time)
                    return &s1 < &s2;
                return s1.time < s2.time;
            }
        };
        std::set<schedule,CompareSchedule> schedules;
    public:
        void update()
        {
            std::set<schedule,CompareSchedule>::iterator lastit;
            bool will_erase = false;
            float now = ofGetElapsedTimef();
            for(std::set<schedule,CompareSchedule>::iterator it(schedules.begin()); it != schedules.end(); ++it)
            {
                if( (*it).time < now  )
                {
                    (*it).delegate->notify(NULL,now);
                    lastit = it;
                    will_erase = true;
                }
                else
                    break;
            }
            if(will_erase)
            {
                schedules.erase(schedules.begin(),++lastit);
            }
 
        }
        template<class ListenerClass>
        void Setup(float time, ListenerClass * target, void (ListenerClass::*listenerMethod)(float&) )
        {
            schedule s;
            s.time = time;
            s.delegate = new Poco::Delegate<ListenerClass,float,false>(target,listenerMethod);
            schedules.insert(s);
        }
    };
public:
    template<class ListenerClass>
    static void Setup(float time, ListenerClass * target, void (ListenerClass::*listenerMethod)(float&) )
    {
        Alarm_detail::Instance().Setup(time,target,listenerMethod);
    }
};
 
 
#endif // ALARM_HPP_INCLUDED
 
