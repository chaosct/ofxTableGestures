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

#ifndef INPUTGESTURETUIO1_13D_H_INCLUDED
#define INPUTGESTURETUIO1_13D_H_INCLUDED



#include <set>
#include "OscInput.hpp"
#include "OscTools.hpp"
#include "InputGestureTuio1.12.5D.hpp"

class InputGestureTuio113D{
    

    public:
    
    typedef InputGestureTuio1125D::commonCursor25DArgs commonCursor3DArgs;
    struct commonObject3DArgs: public commonIdArgs {int f_id ;float xpos;float ypos; float zpos; float aangle; float bangle; float cangle; float xspeed;float yspeed; float zspeed; float aspeed; float bspeed; float cspeed; float maccel; float raccel;};
    
    typedef commonCursor3DArgs addTuioCursor3DArgs;
    typedef commonCursor3DArgs updateTuioCursor3DArgs;
    typedef commonIdArgs removeTuioCursor3DArgs;
    typedef commonObject3DArgs addTuioObject3DArgs;
    typedef commonObject3DArgs updateTuioObject3DArgs;
    typedef commonIdArgs removeTuioObject3DArgs;
    
    static ofEvent<addTuioCursor3DArgs>    addTuioCursor3D;
    static ofEvent<updateTuioCursor3DArgs> updateTuioCursor3D;
    static ofEvent<removeTuioCursor3DArgs> removeTuioCursor3D;
    static ofEvent<addTuioObject3DArgs>    addTuioObject3D;
    static ofEvent<updateTuioObject3DArgs> updateTuioObject3D;
    static ofEvent<removeTuioObject3DArgs> removeTuioObject3D;

    std::set<int> c_s_ids;
    std::set<int> o_s_ids;


        InputGestureTuio113D()
        {
            ofAddListener(OscInput::EventNewOscMessage,this,&InputGestureTuio113D::ReceiveCall);
        }
        virtual ~InputGestureTuio113D()
        {
            ofRemoveListener(OscInput::EventNewOscMessage,this,&InputGestureTuio113D::ReceiveCall);
        }
        void ReceiveCall(OscInput::EventNewOscMessageArgs & args);
        void tuio3Dcur(OscOptionalUnpacker & argList);
        void tuio3Dobj(OscOptionalUnpacker & argList);

};



#endif // INPUTGESTURETUIO1_13D_H_INCLUDED
