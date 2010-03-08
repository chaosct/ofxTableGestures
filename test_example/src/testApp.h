#ifndef _TEST_APP
#define _TEST_APP

#include "TableApp.hpp"

//#include "InputGestureDirectObjects.hpp"
//#include "InputGestureDirectFingers.hpp"
//#include "GestureListener.hpp"
///Example of a class that receives events from direct objects and direct fingers
///inheritance: dummylistener-->CanDirectObjects-->CanDirectFingers-->Listener
//class dummylistener: public tuio::CanDirectObjects < tuio::CanDirectFingers < tuio::GestureListener > >
//{
//    public:
//    virtual void newCursor(int32 id, tuio::DirectFinger *){std::cout << "added direct cur" << std::endl;}
//    virtual void removeCursor(int32 id){std::cout << "removed direct cur" << std::endl;}
//    virtual void newObject(int32 s_id, int32 f_id, tuio::DirectObject *){std::cout << "added direct obj" << std::endl;}
//    virtual void removeObject(int32 s_id, int32 f_id){std::cout << "removed direct obj" << std::endl;}
//};

//#include "Graphic.hpp"
///Example of a class that draws a circle at the middle of the screen
/// it rewrites all methods from 'graphic': draw, update and resize
//class dummyGraphic: public Graphic
//{
//    public:
//        virtual void draw(){
//            ofCircle(ofGetWidth()/2,ofGetHeight()/2,40);
//        }
//        virtual void update(){}
//        virtual void resize(int w, int h){}
//};

//#include "InputGestureDirectFingers.hpp"
//#include "Graphic.hpp"
///Example of a class that draws a circle where the last finger added is
//class dummyListenerGraphic: public tuio::CanDirectFingers < Graphic >
//{
//    tuio::DirectFinger * finger;
//    public:
//        dummyListenerGraphic():finger(NULL){}
//        virtual void draw(){
//            if(finger != NULL) ofCircle(ofGetWidth()*finger->xpos,ofGetHeight()*finger->ypos,20);
//        }
//        virtual void resize(int w, int h){}
//        virtual void newCursor(int32 id, tuio::DirectFinger * _finger){
//            finger = _finger;
//        }
//        virtual void removeCursor(int32 id){
//            if(id == finger->s_id) finger = NULL;
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
