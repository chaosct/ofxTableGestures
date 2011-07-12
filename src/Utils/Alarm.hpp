#ifndef ALARM_HPP_INCLUDED
#define ALARM_HPP_INCLUDED

#include "Singleton.hpp"
#include "Graphic.hpp"

class Alarm: public Graphic, public Singleton<Alarm>
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


#endif // ALARM_HPP_INCLUDED
