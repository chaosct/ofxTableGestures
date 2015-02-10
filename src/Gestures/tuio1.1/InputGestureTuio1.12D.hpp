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

#ifndef INPUTGESTURETUIO1_12D_H_INCLUDED
#define INPUTGESTURETUIO1_12D_H_INCLUDED


#include <set>

#include "ofxGlobalConfig.hpp"
#include "OscInput.hpp"
#include "OscTools.hpp"


class InputGestureTuio112D{
    
public:
    
    struct commonCursor2DArgs: public commonIdArgs
    {
        float xpos;
        float ypos;
        float xspeed;
        float yspeed;
        float maccel;
    };
    
    struct commonBasicObject2DArgs: public commonCursor2DArgs
    {
        float angle;
        float rspeed;
        float raccel;
    };
    
    struct commonObject2DArgs: public commonBasicObject2DArgs
    {
        int f_id ;
    };
    
    struct commonBlob2DArgs: public commonBasicObject2DArgs
    {
        float width;
        float height;
        float area;
    };
    
    
    typedef commonCursor2DArgs addTuioCursor2DArgs;
    typedef commonCursor2DArgs updateTuioCursor2DArgs;
    typedef commonIdArgs removeTuioCursor2DArgs;
    
    typedef commonObject2DArgs addTuioObject2DArgs;
    typedef commonObject2DArgs updateTuioObject2DArgs;
    typedef commonIdArgs removeTuioObject2DArgs;
    
    typedef commonBlob2DArgs addTuioBlob2DArgs;
    typedef commonBlob2DArgs updateTuioBlob2DArgs;
    typedef commonIdArgs removeTuioBlob2DArgs;

    static ofEvent<addTuioCursor2DArgs>    addTuioCursor2D;
    static ofEvent<updateTuioCursor2DArgs> updateTuioCursor2D;
    static ofEvent<removeTuioCursor2DArgs> removeTuioCursor2D;
    static ofEvent<addTuioObject2DArgs>    addTuioObject2D;
    static ofEvent<updateTuioObject2DArgs> updateTuioObject2D;
    static ofEvent<removeTuioObject2DArgs> removeTuioObject2D;
    static ofEvent<addTuioBlob2DArgs>      addTuioBlob2D;
    static ofEvent<updateTuioBlob2DArgs>   updateTuioBlob2D;
    static ofEvent<removeTuioBlob2DArgs>   removeTuioBlob2D;

    std::set<int> c_s_ids;
    std::set<int> o_s_ids;
    std::set<int> b_s_ids;

    int & squaredInterface;
    int & limitroundarea;
    int & limitroundareaobj;
    InputGestureTuio112D():
        squaredInterface(ofxGlobalConfig::getRef("GLOBAL:SQUAREDINTERFACE",1)),
        limitroundarea(ofxGlobalConfig::getRef("GLOBAL:LIMITFINGERSOUTSIDECIRCLE",1)),
        limitroundareaobj(ofxGlobalConfig::getRef("GLOBAL:LIMITOBJECTSOUTSIDECIRCLE",1))
    {
        ofAddListener(OscInput::EventNewOscMessage,this,&InputGestureTuio112D::ReceiveCall);
    }
    virtual ~InputGestureTuio112D()
    {
        ofRemoveListener(OscInput::EventNewOscMessage,this,&InputGestureTuio112D::ReceiveCall);
    }
    void ReceiveCall(OscInput::EventNewOscMessageArgs & args);
    void tuio2Dcur(OscOptionalUnpacker & argList);
    void tuio2Dobj(OscOptionalUnpacker & argList);
    void tuio2Dblb(OscOptionalUnpacker & argList);

};

#endif // INPUTGESTURETUIO1_12D_H_INCLUDED
