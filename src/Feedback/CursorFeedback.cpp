/*

    ofxTableGestures (formerly OF-TangibleFramework)
    Developed for Taller de Sistemes Interactius I
    Universitat Pompeu Fabra

    Copyright (c) 2010 Daniel Gallardo Grassot <daniel.gallardo@upf.edu>

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

#include "CursorFeedback.hpp"

CursorFeedback::CursorFeedback(){
    registerEvent(InputGestureBasicFingers::I().addTuioCursor,&CursorFeedback::addTuioCursor);
    registerEvent(InputGestureBasicFingers::I().updateTuioCursor,&CursorFeedback::updateTuioCursor);
    registerEvent(InputGestureBasicFingers::I().removeTuioCursor,&CursorFeedback::removeTuioCursor);
}


CursorFeedback::~CursorFeedback(){
}

void CursorFeedback::update(){
    float seconds = ofGetElapsedTimef();
    for(std::map<int,HistoryPoint*>::iterator it = finger_map.begin(); it != finger_map.end(); it++){
        it->second->Update(seconds);
    }
}

void CursorFeedback::draw(){
    for(std::map<int,HistoryPoint*>::iterator it = finger_map.begin(); it != finger_map.end(); it++){
       it->second->Draw();
    }
}

void CursorFeedback::addTuioCursor(InputGestureBasicFingers::addTuioCursorArgs & a){
    finger_map[a.id]=new HistoryPoint(a.id,a.xpos,a.ypos);
}

void CursorFeedback::updateTuioCursor(InputGestureBasicFingers::updateTuioCursorArgs & a){
    finger_map[a.id]->SetPoint(a.xpos,a.ypos);
}

void CursorFeedback::removeTuioCursor(InputGestureBasicFingers::removeTuioCursorArgs & a){
    HistoryPoint*tmp = finger_map[a.id];
    finger_map.erase(a.id);
    delete tmp;
}
