/*

    OF-TangibleFramework . Framework for Taller de Sistemes Interactius I
    Universitat Pompeu Fabra

    Copyright (c) 2009 Daniel Gallardo Grassot <daniel.gallardo@upf.edu>

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

#include "CursorFeedback.h"

CursorFeedback::CursorFeedback(){
}

CursorFeedback::~CursorFeedback(){
}

void CursorFeedback::update(){
    float seconds = ofGetElapsedTimef();
    for(std::map<int32,HistoryPoint*>::iterator it = finger_map.begin(); it != finger_map.end(); it++){
        it->second->Update(seconds);
    }
}

void CursorFeedback::draw(){
    for(std::map<int32,HistoryPoint*>::iterator it = finger_map.begin(); it != finger_map.end(); it++){
       it->second->Draw();
    }
}

void CursorFeedback::addTuioCursor(int32 id, float xpos,float ypos,float xspeed,float yspeed,float maccel){
    finger_map[id]=new HistoryPoint(id,xpos,ypos);
}

void CursorFeedback::updateTuioCursor(int32 id, float xpos,float ypos,float xspeed,float yspeed,float maccel){
    finger_map[id]->SetPoint(xpos,ypos);
}

void CursorFeedback::removeTuioCursor(int32 id){
    HistoryPoint*tmp = finger_map[id];
    finger_map.erase(id);
    delete tmp;
}
