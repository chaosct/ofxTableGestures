/*
* Daniel Gallardo Grassot
* daniel.gallardo@upf.edu
* Universitat Pompeu Fabra
* Music Technology Group
*/
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

#include "Grid.hpp"
#include "ofMain.h"

Grid::Grid(int _w_lines, int _h_lines)
{
    w_lines=_w_lines;
    h_lines=_h_lines;
    GenerateOpenGL_lists();
}

Grid::~Grid()
{
    glDeleteLists( grid_list,5);
}

void Grid::Resize()
{
    GenerateOpenGL_lists();
}

void Grid::Draw(bool calibration_enabled, int calibration_mode)
{
    if(calibration_enabled)
    {
        glPushMatrix();
        ofSetColor(255,255,255);
        glCallList(grid_list);
        glColor4f(1,0,0,0.6f);
        switch(calibration_mode)
        {
            case 0: glCallList(grid_list+1); break;
            case 1: glCallList(grid_list+2); break;
            case 2: glCallList(grid_list+3); break;
            case 3: glCallList(grid_list+4); break;
        }
        glPopMatrix();
    }
}

void Grid::GenerateOpenGL_lists()
{
    int width = ofGetWidth();
    int height = ofGetHeight();
    ofSetColor(255,255,255);
    ofSetLineWidth(4.0f);
    int linelength;
    grid_list = glGenLists(5);

    //################################
    // Render the Main Grid
    //################################
    glNewList(grid_list,GL_COMPILE);
    glPushMatrix();
    ///Draws the line-grid depending the dimensions of the screen,
    ///for the reactable, the grid must be square shaped.
    if(width>height)
    {
        linelength = height;
        glTranslatef((width-height)/2,0,0);
        for (int i =0; i<=w_lines; i++)
            ofLine( i*(linelength/w_lines) ,  0 , i*(linelength/w_lines), linelength);
        for (int i =0; i<=h_lines; i++)
            ofLine(0, i*(linelength/h_lines) , linelength, i*(linelength/h_lines));
    }else
    {
        glTranslatef(0,(height-width)/2,0);
        linelength = width;
        for (int i =0; i<=w_lines; i++)
            ofLine( i*(linelength/w_lines) ,  0 , i*(linelength/w_lines), linelength);
        for (int i =0; i<=h_lines; i++)
            ofLine(0, i*(linelength/h_lines) , linelength, i*(linelength/h_lines));
    }
    ofNoFill();
    ///Draws the helping circles of the grid.
    ofSetCircleResolution(60);
    for (int i =0; i<=w_lines/2; i++)
        ofCircle(linelength/2,linelength/2,(i*(linelength/w_lines)));
    ofFill();
    ofSetCircleResolution(20);
    glPopMatrix();
    glEndList();

    //################################
    // Render the "Move" Arrows
    //################################
    glNewList(grid_list+1,GL_COMPILE);
    glPushMatrix();
        if(width>height) glTranslatef((width-height)/2,0,0);
        else glTranslatef(0,(height-width)/2,0);
		glTranslatef(0.5f*linelength,0.55f*linelength,0);
		RenderArrow_two(linelength/2);
		glTranslatef(-0.05*linelength,-0.05f*linelength,0);
		glRotatef(90,0,0,1);
		RenderArrow_two(linelength/2);
	glPopMatrix();
    glEndList();
	//################################
    // Render the "Scale" Arrows
    //################################
    glNewList(grid_list+2,GL_COMPILE);
    glPushMatrix();
        if(width>height) glTranslatef((width-height)/2,0,0);
        else glTranslatef(0,(height-width)/2,0);
		glPushMatrix();
		glTranslatef(0.5f*linelength,0.9f*linelength,0);
		RenderArrow_one(linelength);
		glTranslatef(0,-0.8f*linelength,0);
		glRotatef(180,0,0,1);
		RenderArrow_one(linelength);
		glPopMatrix();
		glTranslatef(0.9f*linelength,0.5f*linelength,0);
		glPushMatrix();
		glRotatef(-90,0,0,1);
		RenderArrow_one(linelength);
		glPopMatrix();
		glTranslatef(-0.8f*linelength,0,0);
		glPushMatrix();
		glRotatef(90,0,0,1);
		RenderArrow_one(linelength);
		glPopMatrix();
	glPopMatrix();
    glEndList();
    //################################
    // Render the "Rotate" Arrows
    //################################
    glNewList(grid_list+3,GL_COMPILE);
	glPushMatrix();
        if(width>height) glTranslatef((width-height)/2,0,0);
        else glTranslatef(0,(height-width)/2,0);
		glTranslatef(0.5f*linelength,0.5f*linelength,0);
		glRotatef(-90,0,0,1);
		DrawArrow_three(linelength);
	glPopMatrix();
    glEndList();
	//################################
    // Render the "Paral" Arrows
    //################################
    glNewList(grid_list+4,GL_COMPILE);
    glPushMatrix();
        if(width>height) glTranslatef((width-height)/2,0,0);
        else glTranslatef(0,(height-width)/2,0);
		glPushMatrix();
		glTranslatef(0.05f*linelength,0.5f*linelength,0);
		glPushMatrix();
		glRotatef(-90,0,0,1);
		glScalef(1,0.5f,1);
		DrawArrow_three(linelength);
		glPopMatrix();
		glPushMatrix();
		glTranslatef(0.9f*linelength,0,0);
		glRotatef(-90,0,0,1);
		glScalef(1,0.5f,1);
		DrawArrow_three(linelength);
		glPopMatrix();
		glPopMatrix();
		glPushMatrix();
		glTranslatef(0.5f*linelength,0.05f*linelength,0);
		glPushMatrix();
		glRotatef(-90,0,0,1);
		glScalef(0.5f,1,1);
		DrawArrow_three(linelength);
		glPopMatrix();
		glPushMatrix();
		glTranslatef(0,0.9f*linelength,0);
		glRotatef(-90,0,0,1);
		glScalef(0.5f,1,1);
		DrawArrow_three(linelength);
		glPopMatrix();
		glPopMatrix();
	glPopMatrix();
	glEndList();
}

void Grid::RenderArrow_one(int size)
{
    glPushMatrix();
    glBegin(GL_TRIANGLE_STRIP);
    glVertex2d(-0.05*size,0);
    glVertex2d(0,0.1*size);
    glVertex2d(0.05*size,0);
    glEnd();
    glBegin(GL_TRIANGLE_FAN);
    glVertex2d(-0.025*size,0);
    glVertex2d(-0.0125*size,-0.1*size);
    glVertex2d(0.0125*size,-0.1*size);
    glVertex2d(0.025*size,0);
    glEnd();
    glPopMatrix();
}

void Grid::RenderArrow_two(int size)
{
    glBegin(GL_TRIANGLE_STRIP);
    glVertex2d(-0.025*size,0);
    glVertex2d(0,0.1*size);
    glVertex2d(0.025*size,0);
    glEnd();
    glBegin(GL_TRIANGLE_FAN);
    glVertex2d(-0.0125*size,0);
    glVertex2d(-0.0125*size,-0.2*size);
    glVertex2d(0.0125*size,-0.2*size);
    glVertex2d(0.0125*size,0);
    glEnd();
    glBegin(GL_TRIANGLE_STRIP);
    glVertex2d(-0.025*size,-0.2*size);
    glVertex2d(0,-0.3*size);
    glVertex2d(0.025*size,-0.2*size);
    glEnd();
}

void Grid::DrawArrow_three(int size){
    glBegin(GL_TRIANGLE_STRIP);
    double arc = M_PI*2-0.7;
    double sinus, cosinus;
    double angle;
    double offset = M_PI /20;
	for (angle=0; angle<arc; angle+=arc/60 ){
		sinus = sin(angle+offset);
		cosinus = cos(angle+offset);
		glVertex2d(0.08*sinus*size, 0.08*cosinus*size);
        glVertex2d(0.1*sinus*size, 0.1*cosinus*size);
	}
	glEnd();

    double ax = 0.08*sinus - 0.1*sinus;
    double ay = 0.08*cosinus - 0.1*cosinus;
    double mod = sqrt(ax*ax + ay*ay);
    ax = ax/mod;
    ay = ay/mod;
	glBegin(GL_TRIANGLES);
        glVertex2d(0.055*sinus*size, 0.055*cosinus*size);
        glVertex2d(0.125*sinus*size, 0.125*cosinus*size);
        glVertex2d((-ay*0.05*size)+0.09*sinus*size, (ax*0.05*size)+0.09*cosinus*size);
	glEnd();
}
