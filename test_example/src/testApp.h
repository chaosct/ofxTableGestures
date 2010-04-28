#ifndef _TEST_APP
#define _TEST_APP

#include "TableApp.hpp"


///Example of a class that receives events from direct objects and direct fingers
///inheritance: dummylistener-->OnTable-->CanDirectObjects-->CanDirectFingers-->Graphic
//#include "InputGestureDirectObjects.hpp"
//#include "InputGestureDirectFingers.hpp"
//#include "Graphic.hpp"
//class dummylistener: public OnTable< tuio::CanDirectObjects < tuio::CanDirectFingers < Graphic > > >
//{
//    public:
//    virtual void newCursor(tuio::DirectFinger *){std::cout << "added direct cur" << std::endl;}
//    virtual void removeCursor(tuio::DirectFinger *){std::cout << "removed direct cur" << std::endl;}
//    virtual void newObject(tuio::DirectObject *){std::cout << "added direct obj" << std::endl;}
//    virtual void removeObject(tuio::DirectObject *){std::cout << "removed direct obj" << std::endl;}
//};


///Example of a class that draws a circle at the middle of the screen
/// it rewrites all methods from 'graphic': draw, update and resize
//#include "Graphic.hpp"
//#include "GlobalConfig.hpp"
//class dummyGraphic: public Graphic
//{
//    public:
//        virtual void draw(){
//            ofCircle(GlobalConfig::getWidth() /2,GlobalConfig::getHeight()/2,0.04);
//        }
//        virtual void update(){}
//        virtual void resize(int w, int h){}
//};

///Example of a class that draws a circle where the last finger added is
//#include "InputGestureDirectFingers.hpp"
//#include "Graphic.hpp"
//class dummyListenerGraphic: public OnTable < tuio::CanDirectFingers < Graphic > >
//{
//    tuio::DirectFinger * finger;
//    public:
//        dummyListenerGraphic():finger(NULL){}
//        virtual void draw(){
//            if(finger != NULL) ofCircle(finger->getX(),finger->getY(),0.02f);
//        }
//        virtual void resize(int w, int h){}
//        virtual void newCursor(tuio::DirectFinger * _finger){
//            finger = _finger;
//        }
//        virtual void removeCursor(tuio::DirectFinger * f){
//            if(f == finger) finger = NULL;
//        }
//};

class testApp : public TableApp{
	public:
        testApp():TableApp(){}
        ///To use render_to_texture, change the constructor for the following line:
        //testApp():TableApp(true){}
		void Setup();
		void Update();
		void Draw();
		void WindowResized(int w, int h);

};

#endif
