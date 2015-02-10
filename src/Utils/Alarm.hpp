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
#include "Poco/Delegate.h"

// Warning! update() method was called automatically, now it isn't anymore
class Alarm
{
private:
    class Alarm_detail : public Singleton<Alarm_detail>
    {
        ///Schedule container
        struct schedule
        {
            void * target;
            float time;
            Poco::AbstractDelegate<float> * delegate;
        };
        
        ///Helper classes
        
        struct CompareSchedule
        {
            bool operator()(const schedule & s1, const schedule & s2)
            {
                if(s1.time == s2.time)
                    return &s1 < &s2;
                return s1.time < s2.time;
            }
        };
        
        struct IsNotOutdated
        {
            float now;
            IsNotOutdated(float t):now(t){}
            bool operator() (const schedule & s)
            {
                return s.time > now;
            }
        };
        
        struct callDelegate
        {
            float now;
            callDelegate(float t):now(t){}
            void operator()(const schedule & s)
            {
                s.delegate->notify(NULL,now);
            }
        };
        
        struct IsListener
        {
            void * li;
            IsListener(void * l):li(l){}
            bool operator()(const schedule & s)
            {
                return s.target == li;
            }
        };
        
        typedef std::set<schedule,CompareSchedule> SetSchedules;
        SetSchedules schedules;
    public:
        void update()
        {
            float now = ofGetElapsedTimef();
            SetSchedules::iterator newbegin = std::find_if(schedules.begin(),schedules.end(),IsNotOutdated(now));
            SetSchedules cschedules(schedules.begin(),newbegin);
            schedules.erase(schedules.begin(),newbegin);
            std::for_each(cschedules.begin(),cschedules.end(),callDelegate(now));
        }

        template<class ListenerClass>
        void Setup(float time, ListenerClass * target, void (ListenerClass::*listenerMethod)(float&) )
        {
            schedule s;
            s.time = time;
            s.delegate = new Poco::Delegate<ListenerClass,float,false>(target,listenerMethod);
            s.target = static_cast<void * >( target);
            schedules.insert(s);
        }
        template<class ListenerClass>
        void Cancel(ListenerClass * target)
        {
            void * vtarget = static_cast<void *>(target);
            std::set<schedule,CompareSchedule> newschedules;
            std::remove_copy_if(schedules.begin(),schedules.end(),std::insert_iterator<SetSchedules>(newschedules,newschedules.begin()),IsListener(vtarget));
            schedules = newschedules;
        }
    };
public:
    template<class ListenerClass>
    static void Setup(float time, ListenerClass * target, void (ListenerClass::*listenerMethod)(float&) )
    {
        Alarm_detail::Instance().Setup(time,target,listenerMethod);
    }
    template<class ListenerClass>
    static void Cancel(ListenerClass * target)
    {
        Alarm_detail::Instance().Cancel(target);
    }
};
 
 
#endif // ALARM_HPP_INCLUDED
 
