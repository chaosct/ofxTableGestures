/*
* Daniel Gallardo Grassot
* daniel.gallardo@upf.edu
* Universitat Pompeu Fabra
* Music Technology Group
*/
/*

    TSIframework . Framework for Taller de Sistemes Interactius I
    Universitat Pompeu Fabra

    Copyright (c) 2009 Daniel Gallardo Grassot <dgallardo@iua.upf.edu>

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

#ifndef _TABLE_APP
#define _TABLE_APP

#include "ofMain.h"
#include "Grid.hpp"

#ifdef SIMULATOR
    #include "Simulator.hpp"
#else
    #warning Simulator not enable, if you need it, define SIMULATOR at project defines
#endif

class TableApp : public ofBaseApp{
    private:
        Grid* grid;
        /// Full/windowed screen
        bool full;
        /// Enable/disable calibration
        bool calibration_enabled;
        /// selector of calibration parameter
        int calibration_mode;
        ///Show/hide help content
        bool show_help;
        ///Show/hide information
        bool show_info;
        ///Enable/disable distortion
        bool distortion_enabled;
        ///Calibration data
        double height_offset;
		double width_offset;
		double center_x;
		double center_y;
		double angle_h;
		double angle_w;
		double angle;
		///Distortion path file
		std::string DistortionPath;
		///Show/hide cursor flag
		bool hide_cursor;
		///Simulator
		#ifdef SIMULATOR
            simulator::Simulator* simulator;
            bool is_simulating;
            bool was_distorsion_enabled;
            bool was_cursor_hide;
        #endif
    public:
        TableApp();
        ~TableApp();
        virtual void Setup()=0;
        virtual void Update()=0;
        virtual void Draw()=0;
        virtual void WindowResized(int w, int h)=0;
        void SaveDistortion();
        void LoadDistortion();
        void DrawInfo();
        void DrawHelp();
        static int GetSquareSide();
	protected:
        void StartDistortion();
        void EndDistortion();
        /// ofBaseApp methods..
		void setup();
		void update();
		void draw();
		void keyPressed  (int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void windowResized(int w, int h);
};

#endif
