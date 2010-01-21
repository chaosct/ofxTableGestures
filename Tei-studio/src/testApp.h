#ifndef _TEST_APP
#define _TEST_APP


#include "ofMain.h"

//Necessari per la calibració
#include "TableApp.hpp"

//Necessari pel reconeixement de gestos
#include "tuioApp.h"
#include "InputGestureClasses.h"
#include "InputGestureFingerObject.h"

#include <map>
#include <list>
#include "CursorFeedback.h"
#include "FigureFeedback.h"

namespace tuio{
class dummylistener: public CanObjectFinger<Listener>
{
    public:
    virtual void objectFingerAdd(DirectObject* obj, DirectFinger* finger) {std::cout << "add" << std::endl;}
    virtual void objectFingerUpdate(DirectObject* obj, DirectFinger* finger) {std::cout << "update" << std::endl;}
    virtual void objectFingerRemove(DirectObject* obj, DirectFinger* finger) {std::cout << "remove" << std::endl;}
    virtual void objectFingerTap(DirectObject* obj, float x, float y) {std::cout << "tap" << std::endl;}
};

class dummylistener2: public CanDirectObjects < CanDirectFingers <Listener> >
{
    public:
    virtual void newCursor(int32 id, DirectFinger *){std::cout << "direct cur" << std::endl;}
    virtual void removeCursor(int32 id){std::cout << "update direct cur" << std::endl;}
    virtual void newObject(int32 s_id, int32 f_id, DirectObject *){std::cout << "direct obj" << std::endl;}
    virtual void removeObject(int32 s_id, int32 f_id){std::cout << "update direct obj" << std::endl;}
};
}

class testApp : public TableApp
{

public:
    tuio::dummylistener* listener;
    tuio::dummylistener2* listener2;
    CursorFeedback* cursorfeedback;
    FigureFeedback* figureFeedback;
    //aquest mètode es crida un cop a l'iniciar l'aplicació
    void Setup();
    //aquest mètode es crida abans de pintar
    void Update();
    //implementeu aquest mètode per pintar
    void Draw();
    //si heu de fer alguna cosa després de redimensionar la finestra, feu-ho aquí
    void WindowResized(int w, int h);

    //afegiu aquí sota els mètodes heretats de les capacitats dels gestos
    //-------------------------------------------------------------------------------------------

};

#endif
