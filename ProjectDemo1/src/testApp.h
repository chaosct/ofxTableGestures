#ifndef _TEST_APP
#define _TEST_APP


#include "ofMain.h"

//Necessari per la calibració
#include "TableApp.hpp"

//Necessari pel reconeixement de gestos
#include "tuioApp.h"
#include "InputGestureClasses.h"
using namespace tuio;

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

class testApp : public tuioApp <TableApp>
{
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
    

};

#endif
