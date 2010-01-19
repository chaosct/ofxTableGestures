#ifndef _TEST_APP
#define _TEST_APP


#include "ofMain.h"

//Necessari per la calibració
#include "TableApp.hpp"

//Necessari pel reconeixement de gestos
#include "tuioApp.h"
#include "InputGestureClasses.h"
#include "InputGestureDummyClick.h"
using namespace tuio;


#include <map>
#include <list>

//La nostra classe principal Derivarà de tuioApp<TableApp>. Si no volguéssiu gestos podrieu
//derivar directament de TableApp.
//Per tal de rebre ghestos heu de definir les capacitats de tuioApp, per exemple, per a rebre
//gestos simples de cursors haurieu de aplicar la capacitat CanBasicFingers de la següent manera:
// class testApp : public CanBasicFingers <tuioApp <TableApp> >
//Si volguéssim afegir-hi una altra capacitat addicional, posem per cas CanDirectObjects, només
//ho hauriem d'encadenar:
// class testApp : public CanDirectObjects < CanBasicFingers <tuioApp <TableApp> > >
//                                     Fixeu-vos sobretot en separar els ">" -----^
//Les capacitats implementades actualment són:
//- CanBasicFingers
//- CanBasicObjects
//- CanDirectFingers
//- CanDirectObjects
//Seguiu la capçalera InputGestureClasses.h per a trobar l'especificació dels gestos corresponents

class MyTimer : public Singleton<MyTimer>
{
    float lasttime;
    float elapsedtime;
    public:
    MyTimer():elapsedtime(0)
    {
        lasttime = ofGetElapsedTimef();
    }
    void step()
    {
        float now = ofGetElapsedTimef();
        elapsedtime = now -lasttime;
        lasttime = now;
        //std::cout << "Time elapsed " << elapsedtime << std::endl;
    }
    float getStep()
    {
        return elapsedtime;
    }
};

class Ring
{
    public:
    double x,y,complete;
    Ring(double X,double Y):x(X),y(Y),complete(0){}
    void Draw()
    {
        if(canremove())return;
        ofSetColor(0,0,255);
        ofNoFill();
        ofCircle(x,y,complete);
        ofFill();
        complete+= MyTimer::Instance().getStep()*100;
        //std::cout << "Complete =  " << complete << std::endl;
    }
    bool canremove()
    {
        return complete >= 100;
    }
};

class testApp : public CanDummyTab <CanDirectObjects< CanDirectFingers <tuioApp <TableApp> > > >
{
private:
    typedef std::map<int32,DirectFinger *> Tcursors;
    typedef std::map<int32,DirectObject *> Tobjects;
    Tcursors cursors;
    Tobjects objects;
    std::list<Ring *> rings;
public:

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

    //CanDirectFingers
    void newCursor(int32 id, DirectFinger *);
    void removeCursor(int32 id);

    //CanDirectObjects
    void newObject(int32 s_id, int32 f_id, DirectObject *);
    void removeObject(int32 s_id, int32 f_id);

    //DummyTab
    void tab(float x,float y);
};

#endif
