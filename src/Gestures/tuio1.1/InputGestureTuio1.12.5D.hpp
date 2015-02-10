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

#ifndef INPUTGESTURETUIO1_12_5D_H_INCLUDED
#define INPUTGESTURETUIO1_12_5D_H_INCLUDED



#include <set>
#include "OscInput.hpp"
#include "OscTools.hpp"
#include "InputGestureTuio1.12D.hpp"


class InputGestureTuio1125D{
    
    public:
    
    struct extraArgsFor25D
    {
        float zpos;
        float zspeed;
    };
    
    struct commonCursor25DArgs: public InputGestureTuio112D::commonCursor2DArgs , public extraArgsFor25D{};
    struct commonObject25DArgs: public InputGestureTuio112D::commonObject2DArgs , public extraArgsFor25D{};
    struct commonBlob25DArgs: public InputGestureTuio112D::commonBlob2DArgs , public extraArgsFor25D{};
    
    typedef commonCursor25DArgs addTuioCursor25DArgs;
    typedef commonCursor25DArgs updateTuioCursor25DArgs;
    typedef commonIdArgs removeTuioCursor25DArgs;
    typedef commonObject25DArgs addTuioObject25DArgs;
    typedef commonObject25DArgs updateTuioObject25DArgs;
    typedef commonIdArgs removeTuioObject25DArgs;
    typedef commonBlob25DArgs addTuioBlob25DArgs;
    typedef commonBlob25DArgs updateTuioBlob25DArgs;
    typedef commonIdArgs removeTuioBlob25DArgs;

    static ofEvent<addTuioCursor25DArgs>       addTuioCursor25D;
    static ofEvent<updateTuioCursor25DArgs>    updateTuioCursor25D;
    static ofEvent<removeTuioCursor25DArgs>    removeTuioCursor25D;
    static ofEvent<addTuioObject25DArgs>       addTuioObject25D;
    static ofEvent<updateTuioObject25DArgs>    updateTuioObject25D;
    static ofEvent<removeTuioObject25DArgs>    removeTuioObject25D;
    static ofEvent<addTuioBlob25DArgs>         addTuioBlob25D;
    static ofEvent<updateTuioBlob25DArgs>      updateTuioBlob25D;
    static ofEvent<removeTuioBlob25DArgs>      removeTuioBlob25D;

    std::set<int> c_s_ids;
    std::set<int> o_s_ids;
    std::set<int> b_s_ids;


    InputGestureTuio1125D()
    {
        ofAddListener(OscInput::EventNewOscMessage,this,&InputGestureTuio1125D::ReceiveCall);
    }
    virtual ~InputGestureTuio1125D()
    {
        ofRemoveListener(OscInput::EventNewOscMessage,this,&InputGestureTuio1125D::ReceiveCall);
    }
    void ReceiveCall(OscInput::EventNewOscMessageArgs & args);
    void tuio25Dcur(OscOptionalUnpacker & argList);
    void tuio25Dobj(OscOptionalUnpacker & argList);
    void tuio25Dblb(OscOptionalUnpacker & argList);
};


#endif // INPUTGESTURETUIO1_12_5D_H_INCLUDED
