#ifndef GLOBALCONFIG_HPP_INCLUDED
#define GLOBALCONFIG_HPP_INCLUDED

#include "Singleton.hpp"
#include <string>
#include <map>
#include "ofxXmlSettings.h"

#include "ofConstants.h"
#ifdef TARGET_WIN32
	#include <process.h>
#else
    #include <pthread.h>
    #include <semaphore.h>
#endif

class GlobalConfig : Singleton<GlobalConfig>
{

class BaseContainer
{
    public:
    virtual void save(){}
};

template<typename T>
class Container : public BaseContainer
{
    T value;
    std::string addr;
    public:
    Container(const std::string& k,const T & defaultvalue = T()):
    addr(k)
    {
        value = GlobalConfig::get<T>(k,defaultvalue);
    }
    T & getRef()
    {
        return value;
    }
    void save()
    {
        GlobalConfig::set<T>(addr,value);
    }
};

ofxXmlSettings XML;

std::map<std::string,BaseContainer*> liveConfig;

void save()
{

    for (std::map<std::string,BaseContainer*>::iterator it = liveConfig.begin();
        it != liveConfig.end(); ++it)
            it->second->save();

    XML.saveFile("GlobalConfig.xml");
}

void load()
{
    std::string message;
    if( XML.loadFile("GlobalConfig.xml") ){
		message = "GlobalConfig.xml loaded!";
	}else{
		message = "unable to load GlobalConfig.xml check data/ folder";
	}
	std::cout << message << std::endl;
}


template<typename T>
static T get(const std::string& k, const T & defaultvalue = T())
{
    GlobalConfig & gc = GlobalConfig::Instance();
    return gc.XML.getValue(k,defaultvalue);
}

template<typename T>
static void set(const std::string& k,const T & t)
{
    GlobalConfig & gc = GlobalConfig::Instance();
    gc.XML.setValue(k,t);
}

#ifdef TARGET_WIN32
        CRITICAL_SECTION  critSec;
#else
        pthread_mutex_t  myMutex;
#endif

void lock(){

   #ifdef TARGET_WIN32
      EnterCriticalSection(&critSec);
   #else
      pthread_mutex_lock(&myMutex);
   #endif
}

void unlock(){

   #ifdef TARGET_WIN32
      LeaveCriticalSection(&critSec);
   #else
      pthread_mutex_unlock(&myMutex);
   #endif
}

public:

GlobalConfig()
{
    #ifdef TARGET_WIN32
      InitializeCriticalSection(&critSec);
    #else
      pthread_mutex_init(&myMutex, NULL);
    #endif
    load();
}
~GlobalConfig()
{
    #ifndef TARGET_WIN32
      pthread_mutex_destroy(&myMutex);
    #endif
    save();
}

template<typename T>
static T & getRef(const std::string& k, const T & defaultvalue = T())
{
    GlobalConfig & gc = GlobalConfig::Instance();
    gc.lock();
    if(gc.liveConfig.find(k)==gc.liveConfig.end())
    {
        gc.liveConfig[k]=new Container<T>(k,defaultvalue);
    }
    Container<T> * c = static_cast<Container<T> *>(gc.liveConfig[k]);
    gc.unlock();
    return c->getRef();
}

};



#endif // GLOBALCONFIG_HPP_INCLUDED
