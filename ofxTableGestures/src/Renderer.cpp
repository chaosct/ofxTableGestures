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

#include <fstream>
#include "ofMain.h"
#include "Renderer.hpp"

#define DISTORTION_PATH "calibration.conf"

Renderer::Renderer():distortion_enabled(false),DistortionPath(DISTORTION_PATH){
    LoadDefaultValues();
    SetIdentity(matrix);
    SetIdentity(imatrix);
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

void Renderer::SetIdentity(double* _matrix){
    for (int i=0;i<4;i++)
        for (int j=0;j<4;j++)
            _matrix[(i*4)+j] = (i==j)?1:0;
}

double * Renderer::GetDistortionMatrix(){
    return matrix;
}

double * Renderer::GetInverseDistortionMatrix(){
    return imatrix;
}

void Renderer::UpdateMatrix(){
    CalculateInverse(4,matrix);
}

void Renderer::CalculateInverse(int n, double* matrix)
{
    double a[16];
    for(int i=0;i<n*n;i++) a[i]=matrix[i];
    double b[16];
    for(int i=0;i<n*n;i++) b[i]=0;
   // double *_imatrix = new double(n*n);
    for(int i=0;i<n*n;i++) imatrix[i]=0;
    for (int i=0; i<n; i++)b[(i*n)+i]=1.0;

//transformación de la matriz y de los términos independientes
    for (int k=0; k<n-1; k++)
    {
        for (int i=k+1; i<n; i++)
        {
//términos independientes
            for (int s=0; s<n; s++)
            {
                b[(i*n)+s]-=a[(i*n)+k]*b[(k*n)+s]/a[(k*n)+k];
            }
//elementos de la matriz
            for (int j=k+1; j<n; j++)
            {
                a[(i*n)+j]-=a[(i*n)+k]*a[(k*n)+j]/a[(k*n)+k];
            }
        }
    }
//cálculo de las incógnitas, elementos de la matriz inversa
    for (int s=0; s<n; s++)
    {
        imatrix[((n-1)*n)+s]=b[((n-1)*n)+s]/a[((n-1)*n)+(n-1)];
        for (int i=n-2; i>=0; i--)
        {
            imatrix[(i*n)+s]=b[(i*n)+s]/a[(i*n)+i];
            for (int k=n-1; k>i; k--)
            {
                imatrix[(i*n)+s]-=a[(i*n)+k]*imatrix[(k*n)+s]/a[(i*n)+i];
            }
        }
    }
//    return c;
}
