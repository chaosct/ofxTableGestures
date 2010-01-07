#ifndef _TEST_APP
#define _TEST_APP


#include "ofMain.h"
#include "tuioApp.h"
#include "TableApp.hpp"
#include "InputGestureClasses.h"

using namespace tuio;

class testApp : public tuioApp <TableApp>
{
private:


public:

    void Setup();
    void Update();
    void Draw();

    void WindowResized(int w, int h);

};

#endif
