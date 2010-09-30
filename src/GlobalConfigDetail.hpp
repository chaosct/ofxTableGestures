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

#ifndef GLOBALCONFIGDETAIL_HPP_INCLUDED

#include "Singleton.hpp"
#include <string>
#include <sstream>
#include <map>
#include "ofxXmlSettings.h"

#include "ofConstants.h"
#ifdef TARGET_WIN32
	#include <process.h>
#else
    #include <pthread.h>
    #include <semaphore.h>
#endif

class GlobalConfigDetail : Singleton<GlobalConfigDetail>
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
        value = GlobalConfigDetail::get<T>(k,defaultvalue);
    }
    T & getRef()
    {
        return value;
    }
    void save()
    {
        GlobalConfigDetail::set<T>(addr,value);
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
    GlobalConfigDetail & gc = GlobalConfigDetail::Instance();
    return gc.XML.getValue(k,defaultvalue);
}

template<typename T>
static void set(const std::string& k,const T & t)
{
    GlobalConfigDetail & gc = GlobalConfigDetail::Instance();
    ///Workaround for strange commas appearing in XML
    std::stringstream s;
    s << t;
    gc.XML.setValue(k,s.str());
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

GlobalConfigDetail()
{
    #ifdef TARGET_WIN32
      InitializeCriticalSection(&critSec);
    #else
      pthread_mutex_init(&myMutex, NULL);
    #endif
    load();
}
~GlobalConfigDetail()
{
    if(getRef("PROGRAM:XML_AUTOSAVE",1))
    {
        std::cout << "Saving xml..." << std::endl;
        save();
    }
    else
    {
        std::cout << "PROGRAM:XML_AUTOSAVE preventing XML to save" << std::endl;
    }

    #ifndef TARGET_WIN32
      pthread_mutex_destroy(&myMutex);
    #endif
}

template<typename T>
static T & getRef(const std::string& k, const T & defaultvalue = T())
{
    GlobalConfigDetail & gc = GlobalConfigDetail::Instance();
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

#define GLOBALCONFIGDETAIL_HPP_INCLUDED



#endif // GLOBALCONFIGDETAIL_HPP_INCLUDED
