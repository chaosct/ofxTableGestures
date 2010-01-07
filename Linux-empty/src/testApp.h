#ifndef _TEST_APP
#define _TEST_APP


#include "ofMain.h"
#include "tuioApp.h"
#include "TableApp.hpp"
#include "InputGestureClasses.h"

using namespace tuio;

class testApp : public CanDirectObjects< CanDirectFingers<tuioApp <TableApp> > >
{
private:

    double dx, dy;
    DirectFinger * mydf;
    DirectObject* mdo;

public:

    void Setup();
    void Update();
    void Draw();

    void updateTuioCursor(int32 id, float xpos,float ypos,float xspeed,float yspeed,float maccel);

    void newCursor(int32 id, DirectFinger * df);
    void removeCursor(int32 id);

    void newObject(int32 s_id, int32 f_id, DirectObject *);
    void removeObject(int32 s_id, int32 f_id);

    void WindowResized(int w, int h);

};

#endif
