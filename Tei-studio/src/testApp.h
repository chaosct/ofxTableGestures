#ifndef _TEST_APP
#define _TEST_APP

///Openframeworks basic
#include "ofMain.h"

///From TableDistortion addon
#include "TableApp.hpp"

///From TuioGestures addon
#include "tuioApp.h"
#include "InputGestureClasses.h"

///Graphics feedback
#include "CursorFeedback.h"
#include "FigureFeedback.h"

///Some figure graphics and gestures
#include "Tangible.hpp"

///Example of a class that receives events from direct objects and direct fingers
///inheritance: dummylistener-->CanDirectObjects-->CanDirectFingers-->Listener
//class dummylistener: public tuio::CanDirectObjects < tuio::CanDirectFingers < tuio::Listener > >
//{
//    public:
//    virtual void newCursor(int32 id, tuio::DirectFinger *){std::cout << "added direct cur" << std::endl;}
//    virtual void removeCursor(int32 id){std::cout << "removed direct cur" << std::endl;}
//    virtual void newObject(int32 s_id, int32 f_id, tuio::DirectObject *){std::cout << "added direct obj" << std::endl;}
//    virtual void removeObject(int32 s_id, int32 f_id){std::cout << "removed direct obj" << std::endl;}
//};

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

///Example of a class that draws a circle where the last finger added is
//class dummyListenerGraphic: public tuio::CanDirectFingers < Graphic >
//{
//    tuio::DirectFinger * finger;
//    public:
//        dummyListenerGraphic():finger(NULL){}
//        virtual void draw(){
//            if(finger != NULL) ofCircle(ofGetWidth()*finger->xpos,ofGetHeight()*finger->ypos,40);
//        }
//        virtual void resize(int w, int h){}
//        virtual void newCursor(int32 id, tuio::DirectFinger * _finger){
//            finger = _finger;
//        }
//        virtual void removeCursor(int32 id){
//            if(id == finger->s_id) finger = NULL;
//        }
//};

///Example of a class that listens the fiducial 4, draws an slider arount it and sends the slider
///value using an osc message. It needs the header :
#include "ofxOscSender.h"
class oscNote : public ShowObjectSlider<Tangible<4> >
{
    public:
    ofxOscSender sender;
    oscNote(){
        sender.setup("127.0.0.1",9999);
    }
    ~oscNote(){Enable(false);}
    void sliderValueUpdated(double n)
    {
        ofxOscMessage message;
        message.setAddress("/sine/freq");
        message.addFloatArg(n*440.0 + 440.0);
        sender.sendMessage(message);
    }
    virtual void Enable(bool flag = true){
        ofxOscMessage message;
        message.setAddress("/sine/volume");
        if(!flag)message.addFloatArg(0);
        else message.addFloatArg(0.1f);
        sender.sendMessage(message);
        Tangible<4>::Enable(flag);
    }
};

///Defining our app. It inherites from TableApp a base class that applies an interface for running applications
///on the table: distortion, load/save configuration files, an integrated table simulator, ...
class testApp : public TableApp
{
    typedef ShowAngleArrowWithMarks< SpinsPerAngle < Tangible<1>, 1, 0, 180 > > proto1;
    ///Objects used in this example:
    // ///dummylistener, it prints at the stdoutput the events from direct cursors and direct fingers
    //dummylistener* listener;
    //dummyGraphic* dummygraphic;
    //dummyListenerGraphic* dummylistenergraphic;
    ///Cursor Feedback. It shows a circle foreach finger on the table
    CursorFeedback* cursorfeedback;
    ///figureFeedback. It shows a 'shape' foreach object on the table
    FigureFeedback* figureFeedback;
    //ShowAngleArrow< SpinsPerAngle < Tangible<3> , 2 > , 25 >* tangible_with_a_white_arrow;
    ShowAngleArrow< Tangible<3> , 25 >* tangible_with_a_white_arrow;
    proto1* angle_arrow_marked;
    oscNote* sine;

public:
    ~testApp();
    ///void Setup();
    ///inputs:none
    ///outputs:none
    ///Desc: this method is called at the begining of our application, it is usually used
    ///for initializate all objects used.
    void Setup();

///Aplication loop

    ///void Update();
    ///inputs:none
    ///outputs:none
    ///Desc: this method is called just before draw, it is usefull for update data.
    void Update();

    ///void Draw();
    ///inputs:none
    ///outputs:none
    ///Desc: where all draws are called
    void Draw();

///End Aplication loop

    ///void WindowResized(int w, int h);
    ///inputs:none
    ///outputs:none
    ///Desc: this method is called after resize the window, usefull for update data that depends on out window size.
    void WindowResized(int w, int h);
};

#endif
