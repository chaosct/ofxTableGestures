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

#include <fstream>
#include "ofMain.h"
#include "Renderer.hpp"

#define DISTORTION_PATH "calibration.conf"

double Renderer::height_offset = 1;
double Renderer::width_offset=1;
double Renderer::center_x=0;
double Renderer::center_y=0;
double Renderer::angle_h=0;
double Renderer::angle_w=0;
double Renderer::angle=0;

Renderer::Renderer():
    DistortionPath(ofToDataPath(DISTORTION_PATH)),
    distortion_enabled(false)
    {
        LoadDefaultValues();
        matrix.makeIdentityMatrix();
    }

Renderer::~Renderer(){}

void Renderer::LoadDistortion(){
    std::ifstream infile(DistortionPath.c_str());
    std::string tmp ("st");
    if(infile.is_open())
    {
        getline(infile,tmp);
        getline(infile,tmp);
        getline(infile,tmp);
        infile >> distortion_enabled;
        getline(infile,tmp);getline(infile,tmp);
        infile >> center_x;
        getline(infile,tmp);getline(infile,tmp);
        infile >> center_y;
        getline(infile,tmp);getline(infile,tmp);
        infile >> height_offset;
        getline(infile,tmp);getline(infile,tmp);
        infile >> width_offset;
        getline(infile,tmp);getline(infile,tmp);
        infile >> angle;
        getline(infile,tmp);getline(infile,tmp);
        infile >> angle_h;
        getline(infile,tmp);getline(infile,tmp);
        infile >> angle_w;
    }
}

void Renderer::SaveDistortion(){
    std::ofstream ofs(DistortionPath.c_str());
    ofs << "#Calibration File for the tabletop framewok" << std::endl;
    ofs << "#" << std::endl;
    ofs << "# Distortion Enabled:" << std::endl;
    ofs << distortion_enabled << std::endl;
    ofs << "# X_offset:" << std::endl;
    ofs << center_x << std::endl;
    ofs << "# y_offset:" << std::endl;
    ofs << center_y << std::endl;
    ofs << "# height_offset:" << std::endl;
    ofs << height_offset << std::endl;
    ofs << "# width_offset:" << std::endl;
    ofs << width_offset << std::endl;
    ofs << "# angle:" << std::endl;
    ofs << angle << std::endl;
    ofs << "# angle_h:" << std::endl;
    ofs << angle_h << std::endl;
    ofs << "# angle_w:" << std::endl;
    ofs << angle_w << std::endl;
}

void Renderer::Enable(){
    distortion_enabled=true;
}

void Renderer::Disable(){
    distortion_enabled=false;
}

void Renderer::Start(){
    if(distortion_enabled)
        StartDistortion();
}

void Renderer::End(){
    if(distortion_enabled)
        EndDistortion();
}

bool Renderer::IsEnabled(){
    return distortion_enabled;
}

std::string Renderer::ToString(){
    std::stringstream msg;
    msg << "  x_position: " << center_x << std::endl;
    msg << "  y_position: " << center_y << std::endl;
    msg << "  height_offset: " << height_offset << std::endl;
    msg << "  width_offset: " << width_offset << std::endl;
    msg << "  angle: " << angle << std::endl;
    msg << "  angle_h: " << angle_h << std::endl;
    msg << "  angle_w: " << angle_w << std::endl;
    return msg.str();
}

void Renderer::LoadDefaultValues(){
    height_offset=1;
    width_offset=1;
    center_x=0;
    center_y=0;
    angle_h=0;
    angle_w=0;
    angle=0;
}

ofMatrix4x4 Renderer::GetDistortionMatrix(){
    return matrix;
}
