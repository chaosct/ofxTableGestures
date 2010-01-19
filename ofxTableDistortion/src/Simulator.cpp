/*

    TSIframework . Framework for Taller de Sistemes Interactius I
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

#include "Simulator.hpp"
#include <fstream>

#define INC_STEP 20
#define CONFIGPATH "simulator.config"
#define M_2PI M_PI*2

namespace simulator
{
    Simulator::Simulator():sessionGenerator(0),fseqGenerator(0),hold(false),select(false),move_selecteds(false),ytray(0){
        #ifdef _ofxOscSENDER_H
        port = DEFAULT_PORT;
        address = DEFAULT_ADDR;
        loaded = LoadConfigFile(CONFIGPATH);
        if(!loaded || load_default){
            std::cout << "Simulator: loading default values" << std::endl;
            for (int i = 0; i< 50; i++){
                object* tmp = new object(-1,i,0,0,0,0,0,0,0,0,i);
                SortObject(tmp);
                objects.push_back(tmp);
            }
        }else std::cout << "Simulator: " << CONFIGPATH << " loaded." << std::endl;
        sender = new ofxOscSender();
        sender->setup(address,port);
        #endif
    }

    Simulator::~Simulator(){
        //SaveFile();
        if(!loaded){
            std::ofstream ofs(CONFIGPATH);
            ofs << "#Simulator config file." << std::endl;
            ofs << "#p -> port" << std::endl;
            ofs << "#a -> address" << std::endl;
            ofs << "#o -> object = fid shape red green blue alpha [sjape = circle, square, star]" << std::endl;
            ofs << "#d -> load default figures" << std::endl;
            ofs << "p " << DEFAULT_PORT << std::endl;
            ofs << "a " << DEFAULT_ADDR << std::endl;
            ofs << "d" << std::endl;
        }
        #ifdef _ofxOscSENDER_H
        delete sender;
        #endif
    }

    bool Simulator::LoadConfigFile(std::string path){
        std::ifstream infile(path.c_str());
        std::string tmp;
        char first;
        load_default = false;
        if(infile.is_open())
        {
            while (!infile.eof()) {
                infile >> first ;
                if(first == '#'){
                    //it is a coment
                }else if(first == 'p'){
                    //set port
                    infile >> port;
                }else if(first == 'a'){
                    //set addr
                    infile >> address;
                }else if(first == 'o'){
                    //set object
                }else if(first == 'd'){
                    load_default= true;
                }
                getline(infile,tmp);
            }
            return true;
        }
        return false;
    }

    void Simulator::SortObject(object* o){
        int x = ofGetWidth()-0.045*ofGetWidth();
        int y = o->tray_number* OBJECT_RADIUS*ofGetHeight();
        o->xpos=x;
        o->ypos=y+ytray+(OBJECT_RADIUS*ofGetHeight()/2);
    }

    bool Simulator::IsAtLateralTray(container* c){
        if(c->xpos>= ofGetWidth()-0.09*ofGetWidth()) return true;
        return false;
    }

    bool Simulator::IsAtBottomTray(container* c){
        if(c->ypos>= ofGetHeight()-0.09*ofGetHeight()) return true;
        return false;
    }

    bool Simulator::IsOnTheScene(container*c){
        if(!IsAtLateralTray(c) && !IsAtBottomTray(c))return true;
        return false;
    }

    void Simulator::Draw(){
        //Draw Object tray..
        ofPushMatrix();
        ofSetColor(100,100,100);
        ofRect(ofGetWidth()-0.09*ofGetWidth(),0,0.09*ofGetWidth(),ofGetHeight());
        ofRect(0,ofGetHeight()-0.09*ofGetHeight(),ofGetWidth()-0.09*ofGetWidth(),0.09*ofGetHeight());
        ofPopMatrix();
        //Draw info...
        ///TODO
        //Draw Cursors..
        for(cursor_list::iterator it = cursors.begin(); it != cursors.end(); it++){
            (*it)->Draw();
        }
        //Draw Objects..
        for(object_list::iterator it = objects.begin(); it != objects.end(); it++){
            (*it)->Draw();
        }
    }

    container* Simulator::Collide(int x, int y,bool only_objects)
    {
        //collide with objects
        for(object_list::iterator it = objects.begin(); it != objects.end(); it++){
            if((*it)->Collide(x,y)){
                (*it)->Add(x,y);
                return (*it);
            }
        }
        if(!only_objects){
            //collide with cursors
            for(cursor_list::iterator it = cursors.begin(); it != cursors.end(); it++){
                if((*it)->Collide(x,y)){
                    (*it)->Add(x,y);
                    return (*it);
                }
            }
            //new cursor
            cursor* new_cursor = new cursor(sessionGenerator++,x,y,0,0,0);
            cursors.push_back(new_cursor);
            cursorUpdated(new_cursor);
            return new_cursor;
        }
        return NULL;
    }

    void Simulator::mouseDragged(int x, int y, int button){
        if(button==0){
            for(object_list::iterator it = objects.begin(); it != objects.end(); it++){
                if((*it)->mouse_on){
                    (*it)->Update(x,y);
                    if(select){
                        (*it)->isUp=true;
                        objectRemoved(*it);
                        (*it)->sid = -1;
                    }
                    else{
                        (*it)->isUp=false;
                        objectUpdated(*it);
                    }
                    return;
                }
            }
            //selected cursors
            if(move_selecteds)
            {
                for(cursor_list::iterator it = cursors.begin(); it != cursors.end(); it++){
                    if((*it)->isSelected)
                    {
                        (*it)->Update(x,y);
                        cursorUpdated(*it);
                    }
                }
                return;
            }
            //cursors
            for(cursor_list::iterator it = cursors.begin(); it != cursors.end(); it++){
                if((*it)->mouse_on){
                    (*it)->Update(x,y);
                    cursorUpdated(*it);
                }
            }
        }
        else if(button == 2 && previous_y != -1){
            int increment = y-previous_y;
            for(object_list::iterator it = objects.begin(); it != objects.end(); it++){
                if((*it)->mouse_on){
                    (*it)->angle += (2*PI*increment)/100;
                    if((*it)->angle >= M_2PI)(*it)->angle = (*it)->angle-M_2PI;
                    if((*it)->angle < 0)(*it)->angle = (*it)->angle+M_2PI;
                    if(!(*it)->isUp)objectUpdated(*it);
                }
            }
            previous_y = y;
        }
    }

    void Simulator::mousePressed(int x, int y, int button){
        if(button == 0 ){
            container* tmp = Collide (x,y);
            tmp->mouse_on=true;
            cursor* c = dynamic_cast<cursor*> (tmp);
            if(c!=NULL && c->isSelected)
            {
                move_selecteds=true;
                for(cursor_list::iterator it = cursors.begin(); it != cursors.end(); it++){
                    if((*it)->isSelected)(*it)->Add(x,y);
                }
            }
            object* o = dynamic_cast<object*>(tmp);
            if(o != NULL){
                if(select){
                    o->isUp=true;
                    objectRemoved(o);
                    o->sid = -1;
                }
                else{
                    o->isUp=false;
                    objectUpdated(o);
                }
            }
        }
        else if(button == 3){
            MoveYTray(INC_STEP);
        }
        else if(button == 4){
            MoveYTray(-INC_STEP);
        }
        else if(button == 2){
            container* tmp = Collide (x,y,true);
            if(tmp != NULL){
                previous_y = y;
                tmp->mouse_on=true;
            }
            else
                previous_y = -1;
        }
    }

    void Simulator::mouseReleased(int x, int y, int button){
        if(button == 0){
            //Unselect objects
            for(object_list::iterator it = objects.begin(); it != objects.end(); it++){
                if((*it)->mouse_on){
                    (*it)->mouse_on=false;
                    if(IsAtLateralTray(*it)) SortObject(*it);
                    if(select){
                        (*it)->isUp=true;
                        objectRemoved(*it);
                        (*it)->sid = -1;
                    }
                    else{
                        (*it)->isUp=false;
                        objectUpdated(*it);
                    }
                }
            }
            std::vector<int> todelete;
            int i = 0;
            //Unselect cursors
            for(cursor_list::iterator it = cursors.begin(); it != cursors.end(); it++){
                if((*it)->mouse_on){
                    (*it)->mouse_on=false;
                    if(!hold && !(*it)->isHolded)todelete.push_back(i);
                    if(hold && (*it)->isHolded){
                        (*it)->isHolded=false;
                        todelete.push_back(i);
                    }
                    else (*it)->isHolded = true;
                    if((*it)->isHolded && select){
                        (*it)->isSelected = !(*it)->isSelected;
                    }
                    move_selecteds=false;
                }
                i++;
            }
            //erase cursors
            for( std::vector<int>::iterator it = todelete.begin(); it != todelete.end(); it++ ){
                cursor* tmp = cursors[(*it)];
                int k = *it;
                cursors.erase(cursors.begin()+k);
                cursorDeleted(tmp);
                delete(tmp);
            }
        }
        else if(button == 2){
            for(object_list::iterator it = objects.begin(); it != objects.end(); it++){
                if((*it)->mouse_on)(*it)->mouse_on=false;
            }
        }
    }

    void Simulator::Hold(bool stat){
        hold = stat;
    }

    void Simulator::Select(bool stat){
        select = stat;
    }

    void Simulator::MoveYTray(int step){
        ytray+=step;

        if(ytray > 0){
            ytray=0;
            return;
        }
        float max = (objects.size()-14)* OBJECT_RADIUS*ofGetHeight()*-1;
        if(ytray < max){
            ytray=max;
            return;
        }

        for(object_list::iterator it = objects.begin(); it != objects.end(); it++){
            if(IsAtLateralTray(*it)) (*it)->ypos+=step;
        }
    }

    void Simulator::Reset(){
        for(object_list::iterator it = objects.begin(); it != objects.end(); it++) SortObject(*it);
        for(cursor_list::iterator it = cursors.begin(); it != cursors.end(); it++){
            cursorDeleted(*it);
            delete (*it);
        }
        cursors.clear();

        cursors_escene.clear();
        objects_escene.clear();
        removeTuioCursor(NULL);
        removeTuioObject(NULL);
    }

    cursor_list::iterator Simulator::IsAtCursorList(cursor* c){
        for(cursor_list::iterator it = cursors_escene.begin(); it != cursors_escene.end(); it++){
            if((*it)->sid == c->sid) return it;
        }
        return cursors_escene.end();
    }

    object_list::iterator Simulator::IsAtObjectList(object* o){
        for(object_list::iterator it = objects_escene.begin(); it != objects_escene.end(); it++){
            if((*it)->sid == o->sid) return it;
        }
        return objects_escene.end();
    }

    ///Message generators...
    void Simulator::cursorUpdated(cursor* c){
        cursor_list::iterator it = IsAtCursorList(c);
        if(IsOnTheScene(c)){
            if(it != cursors_escene.end()){
                //update cur
                updateTuioCursor(c);
            }else{
                //add cur
                addTuioCursor(c);
                cursors_escene.push_back(c);
            }
        }else{
            if(it != cursors_escene.end()){
                //remove cur
                cursors_escene.erase(it);
                removeTuioCursor(c);
                c->sid = sessionGenerator++;
            }
        }
    }

    void Simulator::cursorDeleted(cursor* c){
        cursor_list::iterator it = IsAtCursorList(c);
        if(it != cursors_escene.end()){
            //remove cur
            cursors_escene.erase(it);
            removeTuioCursor(c);
        }
    }

    void Simulator::objectUpdated(object* o){
        if(o->isUp){
            objectRemoved(o);
            return;
        }

        object_list::iterator it = IsAtObjectList(o);
        if(IsOnTheScene(o)){
            if(it != objects_escene.end()){
                //update obj
                updateTuioObject(o);
            }else{
                //add obj
                o->sid= sessionGenerator++;
                addTuioObject(o);
                objects_escene.push_back(o);
            }
        }else{
            if(it != objects_escene.end()){
                //remove obj
                objects_escene.erase(it);
                removeTuioObject(o);
                o->sid = -1;
            }
        }

    }

    void Simulator::objectRemoved(object* o){
        object_list::iterator it = IsAtObjectList(o);
        if(it != objects_escene.end()){
            //remove obj
            objects_escene.erase(it);
            removeTuioObject(o);
            o->sid = -1;
        }
    }

    void Simulator::addTuioObject(object* o){
        #ifdef _ofxOscSENDER_H
            ofxOscBundle Bundle;
            //alive message
            ofxOscMessage message_alive;
            message_alive.setAddress("/tuio/2Dobj");
            message_alive.addStringArg("alive");
            for(object_list::iterator it = objects_escene.begin(); it != objects_escene.end(); it++){
                message_alive.addIntArg((*it)->sid);
            }
            //set message
            ofxOscMessage message_set;
            message_set.setAddress("/tuio/2Dobj");
            message_set.addStringArg("set");
            message_set.addIntArg(o->sid);
            message_set.addIntArg(o->fid);
            message_set.addFloatArg( (((float)o->xpos)/ofGetWidth())*1.1f );
            message_set.addFloatArg( (((float)o->ypos)/ofGetHeight())*1.1f );
            message_set.addFloatArg( o->angle );
            message_set.addFloatArg(o->xspeed);
            message_set.addFloatArg(o->yspeed);
            message_set.addFloatArg(o->rspeed);
            message_set.addFloatArg(o->maccel);
            message_set.addFloatArg(o->raccel);
            //fseq message
            fseqGenerator++;
            ofxOscMessage message_frame;
            message_frame.setAddress("/tuio/2Dobj");
            message_frame.addStringArg("fseq");
            message_frame.addIntArg(fseqGenerator);
            //build bundle
            Bundle.addMessage(message_alive);
            Bundle.addMessage(message_set);
            Bundle.addMessage(message_frame);
            sender->sendBundle(Bundle);
        #else
            std::cout << "obj add\t\t" << o->sid << " " << o->fid << " " << o->xpos/ofGetWidth() << " " << o->ypos/ofGetHeight() << " " << o->angle << std::endl;
        #endif
    }

    void Simulator::updateTuioObject(object* o){
        #ifdef _ofxOscSENDER_H
            ofxOscBundle Bundle;
            //alive message
            ofxOscMessage message_alive;
            message_alive.setAddress("/tuio/2Dobj");
            message_alive.addStringArg("alive");
            for(object_list::iterator it = objects_escene.begin(); it != objects_escene.end(); it++){
                message_alive.addIntArg((*it)->sid);
            }
            //set message
            ofxOscMessage message_set;
            message_set.setAddress("/tuio/2Dobj");
            message_set.addStringArg("set");
            message_set.addIntArg(o->sid);
            message_set.addIntArg(o->fid);
            message_set.addFloatArg( (((float)o->xpos)/ofGetWidth())*1.1f );
            message_set.addFloatArg( (((float)o->ypos)/ofGetHeight())*1.1f );
            message_set.addFloatArg(o->angle);
            message_set.addFloatArg(o->xspeed);
            message_set.addFloatArg(o->yspeed);
            message_set.addFloatArg(o->rspeed);
            message_set.addFloatArg(o->maccel);
            message_set.addFloatArg(o->raccel);
            //fseq message
            fseqGenerator++;
            ofxOscMessage message_frame;
            message_frame.setAddress("/tuio/2Dobj");
            message_frame.addStringArg("fseq");
            message_frame.addIntArg(fseqGenerator);
            //build bundle
            Bundle.addMessage(message_alive);
            Bundle.addMessage(message_set);
            Bundle.addMessage(message_frame);
            sender->sendBundle(Bundle);
        #else
            std::cout << "obj update\t" << o->sid << " " << o->fid << " " << o->xpos << " " << o->ypos << " " << o->angle << std::endl;
        #endif
    }

    void Simulator::removeTuioObject(object* o){
        #ifdef _ofxOscSENDER_H
            ofxOscBundle Bundle;
            ofxOscMessage message_alive;
            message_alive.setAddress("/tuio/2Dobj");
            message_alive.addStringArg("alive");
            for(object_list::iterator it = objects_escene.begin(); it != objects_escene.end(); it++){
                message_alive.addIntArg((*it)->sid);
            }
            fseqGenerator++;
            ofxOscMessage message_frame;
            message_frame.setAddress("/tuio/2Dobj");
            message_frame.addStringArg("fseq");
            message_frame.addIntArg(fseqGenerator);
            Bundle.addMessage(message_alive);
            Bundle.addMessage(message_frame);
            sender->sendBundle(Bundle);
        #else
            std::cout << "obj remove\t" << o->sid << std::endl;
        #endif
    }

    void Simulator::addTuioCursor(cursor* c){
        #ifdef _ofxOscSENDER_H
            ofxOscBundle Bundle;
            //alive message
            ofxOscMessage message_alive;
            message_alive.setAddress("/tuio/2Dcur");
            message_alive.addStringArg("alive");
            for(cursor_list::iterator it = cursors_escene.begin(); it != cursors_escene.end(); it++){
                message_alive.addIntArg((*it)->sid);
            }
            //set message
            ofxOscMessage message_set;
            message_set.setAddress("/tuio/2Dcur");
            message_set.addStringArg("set");
            message_set.addIntArg(c->sid);
            message_set.addFloatArg( (((float)c->xpos)/ofGetWidth())*1.1f );
            message_set.addFloatArg( (((float)c->ypos)/ofGetHeight())*1.1f );
            message_set.addFloatArg(c->xspeed);
            message_set.addFloatArg(c->yspeed);
            message_set.addFloatArg(c->maccel);
            //fseq message
            fseqGenerator++;
            ofxOscMessage message_frame;
            message_frame.setAddress("/tuio/2Dcur");
            message_frame.addStringArg("fseq");
            message_frame.addIntArg(fseqGenerator);
            //build bundle
            Bundle.addMessage(message_alive);
            Bundle.addMessage(message_set);
            Bundle.addMessage(message_frame);
            sender->sendBundle(Bundle);
        #else
            std::cout << "cur add\t\t" << c->sid << " " << c->xpos << " " << c->ypos << std::endl;
        #endif
    }

    void Simulator::updateTuioCursor(cursor* c){
        #ifdef _ofxOscSENDER_H
            ofxOscBundle Bundle;
            //alive message
            ofxOscMessage message_alive;
            message_alive.setAddress("/tuio/2Dcur");
            message_alive.addStringArg("alive");
            for(cursor_list::iterator it = cursors_escene.begin(); it != cursors_escene.end(); it++){
                message_alive.addIntArg((*it)->sid);
            }
            //set message
            ofxOscMessage message_set;
            message_set.setAddress("/tuio/2Dcur");
            message_set.addStringArg("set");
            message_set.addIntArg(c->sid);
            message_set.addFloatArg( (((float)c->xpos)/ofGetWidth())*1.1f );
            message_set.addFloatArg( (((float)c->ypos)/ofGetHeight())*1.1f );
            message_set.addFloatArg(c->xspeed);
            message_set.addFloatArg(c->yspeed);
            message_set.addFloatArg(c->maccel);
            //fseq message
            fseqGenerator++;
            ofxOscMessage message_frame;
            message_frame.setAddress("/tuio/2Dcur");
            message_frame.addStringArg("fseq");
            message_frame.addIntArg(fseqGenerator);
            //build bundle
            Bundle.addMessage(message_alive);
            Bundle.addMessage(message_set);
            Bundle.addMessage(message_frame);
            sender->sendBundle(Bundle);
        #else
            std::cout << "cur update\t" << c->sid << " " << c->xpos << " " << c->ypos << std::endl;
        #endif
    }

    void Simulator::removeTuioCursor(cursor* c){
        #ifdef _ofxOscSENDER_H
            ofxOscBundle Bundle;
            ofxOscMessage message_alive;
            message_alive.setAddress("/tuio/2Dcur");
            message_alive.addStringArg("alive");
            for(cursor_list::iterator it = cursors_escene.begin(); it != cursors_escene.end(); it++){
                message_alive.addIntArg((*it)->sid);
            }
            fseqGenerator++;
            ofxOscMessage message_frame;
            message_frame.setAddress("/tuio/2Dcur");
            message_frame.addStringArg("fseq");
            message_frame.addIntArg(fseqGenerator);
            Bundle.addMessage(message_alive);
            Bundle.addMessage(message_frame);
            sender->sendBundle(Bundle);
        #else
            std::cout << "cur remove\t" << c->sid << std::endl;
        #endif
    }

    ///missatge cada segon?

}
