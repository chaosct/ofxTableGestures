#include "CursorFeedback.h"

CursorFeedback::CursorFeedback(){
}

CursorFeedback::~CursorFeedback(){
}

void CursorFeedback::Update(){
    float seconds = ofGetElapsedTimef();
    for(std::map<int32,HistoryPoint*>::iterator it = finger_map.begin(); it != finger_map.end(); it++){
        it->second->Update(seconds);
    }
}

void CursorFeedback::Draw(){
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
