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

#include "FigureFeedback.hpp"

FigureFeedback::FigureFeedback(){
}

FigureFeedback::~FigureFeedback(){
}

void FigureFeedback::update(){
    std::list<HistoryFigure*>::iterator it = to_delete.begin();
    float time = ofGetElapsedTimef();
    while (it != to_delete.end()){
        (*it)->Update(time);
        if((*it)->CanDelete()){
            std::list<HistoryFigure*>::iterator tmp = it;
            it++;
            objects.erase((*tmp)->dobj->s_id);
            to_delete.erase(tmp);
        }
        else it++;
    }
}

void FigureFeedback::draw(){
    for (std::map<int32,HistoryFigure*>::iterator it = objects.begin(); it != objects.end(); it++){
        it->second->draw();
    }
}

void FigureFeedback::newObject(tuio::DirectObject * object){
    objects[object->s_id]= new HistoryFigure(object);
}

void FigureFeedback::removeObject(tuio::DirectObject * object){
    objects[object->s_id]->Release(ofGetElapsedTimef());
    to_delete.push_back(objects[object->s_id]);
}
