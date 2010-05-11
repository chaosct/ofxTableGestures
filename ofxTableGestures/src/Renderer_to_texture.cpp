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

#include "Renderer_to_texture.hpp"

Renderer_to_texture::Renderer_to_texture(){
    w = ofGetWidth();
    h = ofGetHeight();
    texScreen.allocate(w,h,GL_RGB);
}

Renderer_to_texture::~Renderer_to_texture(){
}

void Renderer_to_texture::StartDistortion(){
    //nothing to do
}

void Renderer_to_texture::EndDistortion(){
    ///Grabs the output screen
    texScreen.loadScreenData(0,0,w,h);
    ///clears the screen
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
    ///aplies some transformations
    ofSetColor(255,255,255);
    glPushMatrix();
    glTranslated(center_x,center_y,0);
    glTranslatef(0.5f,0.5f,0);
    glRotated(angle,0,0,1);
    glRotated(angle_h,1,0,0);
    glRotated(angle_w,0,1,0);
    glScaled(width_offset,height_offset,1);
    glTranslatef(-0.5f,-0.5f,0);
    //glGetDoublev(GL_MODELVIEW_MATRIX,Renderer::matrix);
//    std::cout << matrix[0] << "\t" << matrix[4] << "\t" << matrix[8] << "\t"<< matrix[12] << std::endl;
//    std::cout << matrix[1] << "\t" << matrix[5] << "\t" << matrix[9] << "\t"<< matrix[13] << std::endl;
//    std::cout << matrix[2] << "\t" << matrix[6] << "\t" << matrix[10] << "\t"<< matrix[14] << std::endl;
//    std::cout << matrix[3] << "\t" << matrix[7] << "\t" << matrix[11] << "\t"<< matrix[15] << std::endl;
//    std::cout << std::endl;

    ///Draws the texture
    texScreen.draw(0,0);
    glPopMatrix();
}

