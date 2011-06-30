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

#include "Shapes.hpp"

#define SQUARE_RADIUS 60
#define SQAURE_BOUND 22.5f
#define SQUARE_VERTEX 2

#define CIRCLE_RADIUS 35

#define STAR_OUTER_RADIUS 35
#define STAR_INNER_RADIUS 30
#define STAR_EDGES 24

//#define CONFIGPATH "../simulator.config"

#include "ofUtils.h"
#include <fstream>

using namespace shapes;

Shape::~Shape(){}

shapeSquare::shapeSquare(bool _round_edges):round_edges(_round_edges){
}

void shapeSquare::draw(){

    if(round_edges){
        ofPushMatrix();
        ofTranslate(-SQUARE_RADIUS/2,-SQUARE_RADIUS/2);
        ofBeginShape();
            ofCurveVertex(SQUARE_RADIUS-SQAURE_BOUND,0);
            ofCurveVertex(SQUARE_RADIUS-SQAURE_BOUND,0);
            ofCurveVertex(SQUARE_RADIUS-SQUARE_VERTEX,SQUARE_VERTEX);
            ofCurveVertex(SQUARE_RADIUS,SQAURE_BOUND);
            ofCurveVertex(SQUARE_RADIUS,SQAURE_BOUND);
            ofCurveVertex(SQUARE_RADIUS,SQUARE_RADIUS-SQAURE_BOUND);
            ofCurveVertex(SQUARE_RADIUS,SQUARE_RADIUS-SQAURE_BOUND);
            ofCurveVertex(SQUARE_RADIUS-SQUARE_VERTEX,SQUARE_RADIUS-SQUARE_VERTEX);
            ofCurveVertex(SQUARE_RADIUS-SQAURE_BOUND,SQUARE_RADIUS);
            ofCurveVertex(SQUARE_RADIUS-SQAURE_BOUND,SQUARE_RADIUS);
            ofCurveVertex(SQAURE_BOUND,SQUARE_RADIUS);
            ofCurveVertex(SQAURE_BOUND,SQUARE_RADIUS);
            ofCurveVertex(SQUARE_VERTEX,SQUARE_RADIUS-SQUARE_VERTEX);
            ofCurveVertex(0,SQUARE_RADIUS-SQAURE_BOUND);
            ofCurveVertex(0,SQUARE_RADIUS-SQAURE_BOUND);
            ofCurveVertex(0,SQAURE_BOUND);
            ofCurveVertex(0,SQAURE_BOUND);
            ofCurveVertex(SQUARE_VERTEX, SQUARE_VERTEX);
            ofCurveVertex(SQAURE_BOUND,0);
            ofCurveVertex(SQAURE_BOUND,0);
        ofEndShape(true);
        ofPopMatrix();
    }else{
        ofPushMatrix();
        ofTranslate(-SQUARE_RADIUS/2,-SQUARE_RADIUS/2);
        ofBeginShape();
            ofVertex(0,0);
            ofVertex(SQUARE_RADIUS,0);
            ofVertex(SQUARE_RADIUS,SQUARE_RADIUS);
            ofVertex(0,SQUARE_RADIUS);
        ofEndShape(true);
        ofPopMatrix();
    }
}

void shapeCircle::draw(){
    ofCircle(0,0,CIRCLE_RADIUS);
}

void shapeStar::draw()
{
    float angleChangePerPt = TWO_PI / (float)STAR_EDGES;
    float angle = 0;
    ofBeginShape();
        for (int i = 0; i < STAR_EDGES; i++){
		if (i % 2 == 0) {
			// inside point:
			float x = STAR_INNER_RADIUS * cos(angle);
			float y = STAR_INNER_RADIUS * sin(angle);
			ofVertex(x,y);
		} else {
			// outside point
			float x = STAR_OUTER_RADIUS * cos(angle);
			float y = STAR_OUTER_RADIUS * sin(angle);
			ofVertex(x,y);
		}
		angle += angleChangePerPt;
	}
	ofEndShape();
}

void shapeDodecahedron::draw(){
    float angleChangePerPt = TWO_PI / 12.0f;
    float angle = 0;
    ofBeginShape();
    for (int i = 0; i < 12; i++){
        float x = STAR_OUTER_RADIUS * cos(angle);
        float y = STAR_OUTER_RADIUS * sin(angle);
        ofVertex(x,y);
        angle += angleChangePerPt;
	}
	ofEndShape();
}

void shapePentagon::draw()
{
    float angleChangePerPt = TWO_PI / 5.0f;
    float angle = 0;
    ofBeginShape();
    for (int i = 0; i < 5; i++){
        float x = STAR_OUTER_RADIUS * cos(angle);
        float y = STAR_OUTER_RADIUS * sin(angle);
        ofVertex(x,y);
        angle += angleChangePerPt;
	}
	ofEndShape();
}

shape_color::shape_color(int _shapeid, int _r, int _g, int _b):shapeid(_shapeid),r(_r),g(_g),b(_b){}

void shape_color::draw(bool draw_color){
    if(draw_color)ofSetColor(r,g,b);
    if(shapeid == SQUARE){
        shapeSquare sq;
        sq.draw();
    }else if(shapeid == CIRCLE){
        shapeCircle c;
        c.draw();
    }else if(shapeid == PENTAGON){
        shapePentagon p;
        p.draw();
    }else if(shapeid == DODECAHEDRON){
        shapeDodecahedron d;
        d.draw();
    }else if(shapeid == STAR){
        shapeStar s;
        s.draw();
    }else if(shapeid == SQUARE_ROUNDED){
        shapeSquare sq(true);
        sq.draw();
    }
}

shapes::Figure_shape* shapes::Figure_shape::pinstance = NULL;

Figure_shape::Figure_shape(){
    Load();
}

Figure_shape& Figure_shape::Instance(){
    if (pinstance == NULL)
        pinstance = new Figure_shape();
    return *pinstance;
}

Figure_shape::~Figure_shape(){
    objectid_shape.clear();
}

void Figure_shape::Load()
{
    std::ifstream infile(ofToDataPath(NAMEPATH).c_str());
    std::string tmp;
    char first;
    int f_id, r,g,b, a;
    std::string shape;
    int n_shape;
    if(infile.is_open()){
        while (!infile.eof()){
            infile >> first;
            if(first == 'o'){
                f_id = 0;
                r = g = b = 100;
                n_shape = 0;
                infile >> f_id >> shape >> r >> g >> b >> a;
                if(shape.compare("circle")== 0)n_shape=CIRCLE;
                else if(shape.compare("square")== 0)n_shape=SQUARE;
                else if(shape.compare("star")== 0)n_shape=STAR;
                else if(shape.compare("square_rounded")== 0)n_shape=SQUARE_ROUNDED;
                else if(shape.compare("pentagon")== 0)n_shape=PENTAGON;
                else if(shape.compare("dodecahedron")== 0)n_shape=DODECAHEDRON;
                //std::cout << f_id << " " << n_shape<< " " << r<< " " << g<< " " << b<< " " << a<<std::endl;
                objectid_shape[f_id]=new shape_color(n_shape, r, g, b);
            }
            getline(infile,tmp);
            first = 0;
        }
    }
    if(objectid_shape.size()==0)
        objectid_shape[0]=new shape_color(0, 100, 100, 100);
}

shape_color* Figure_shape::GetShape(int f_id){
    std::map<int, shape_color*>::iterator it = objectid_shape.find(f_id);
    if(it != objectid_shape.end()) return it->second;
    else return objectid_shape[0];
}

void Figure_shape::drawShape(int f_id,bool add_color){
    std::map<int, shape_color*>::iterator it = objectid_shape.find(f_id);
    if(it != objectid_shape.end()) it->second->draw(add_color);
    else return objectid_shape[0]->draw(add_color);
}

std::list<int> Figure_shape::GetFiducialIds(){
    std::list<int> toreturn;
    for (std::map<int, shape_color*>::iterator it=objectid_shape.begin(); it !=objectid_shape.end(); it++){
        toreturn.push_back(it->first);
    }
    return toreturn;
}
