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

#ifndef _RENDERER
#define _RENDERER

#include <string>

class Renderer{
    public:
        ///Calibration data:
            ///height scale factor
        double height_offset;
            ///width scale factor
		double width_offset;
            ///x position
		double center_x;
            ///y position
		double center_y;
            ///y rotation angle
		double angle_h;
            ///x rotation angle
		double angle_w;
            ///z rotation angle
		double angle;
		///Distortion path file
		std::string DistortionPath;
        ///Enable/disable distortion flag
        bool distortion_enabled;
    protected:
        virtual void StartDistortion()=0;
        virtual void EndDistortion()=0;
    public:
        Renderer():distortion_enabled(false){}
        virtual ~Renderer()=0;
        virtual void LoadDistortion();
        virtual void SaveDistortion();
        void Start();
        void End();
        virtual void Enable();
        virtual void Disable();
        virtual bool IsEnabled();
        virtual std::string ToString();
        void LoadDefaultValues();
};

#endif
