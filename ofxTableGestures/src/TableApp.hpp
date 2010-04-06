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

#ifndef _TABLE_APP
#define _TABLE_APP

#include "ofMain.h"
#include "Grid.hpp"
#include "Renderer.hpp"

///By defining the global "SIMULATOR", it enables the integrated simulator.
///When it is enabled, it can be activated by tapping the 's' key.
#ifdef SIMULATOR
    #include "Simulator.hpp"
#else
    #warning Simulator not enabled, if you need it, define SIMULATOR at project defines
#endif

///Table App is an interface class to deal with all table calibration processes, simulator mode and
///abstractize the dispatchers from the main aplication of this project
class TableApp : public ofBaseApp{
    ///The data contained by this class is private and it is mainly used for distortionate the output,
    ///draws the calibration grid and draws the simulator scene.
    private:
        ///Renderer: used for distortionate the graphic output.
        Renderer *renderer;
        ///Grid: used for drawing the calibration grid on the screen.
        Grid* grid;
        ///Show grid flag
        bool show_grid;
        /// Full/windowed screen flag
        bool full;
        /// selector of calibration parameter
        /// translate, rotate, scale, rotate x and y axes,...
        int calibration_mode;
        ///Show/hide help content flag
        bool show_help;
        ///Show/hide information flag
        bool show_info;
		///Show/hide cursor flag
		bool hide_cursor;
		///Simulator
		#ifdef SIMULATOR
            simulator::Simulator* simulator;
            ///Simulator enabled flag
            bool is_simulating;
            ///distortion status before enable simulator.
            bool was_distorsion_enabled;
            ///cursor status before enable simulator.
            bool was_cursor_hide;
        #endif
        static double* calibration_matrix;
    public:
        ///Constructor, here is initialized all data
        ///and loaded distortion parameters from file.
        TableApp(bool use_render_to_texture = false);
        ///Destructor
        ~TableApp();
        /// pure virtual methods to be rewrited
        virtual void Setup()=0;
        virtual void Update()=0;
        virtual void Draw()=0;
        virtual void WindowResized(int w, int h)=0;
        /// Draws text screen information
        void DrawInfo();
        /// Draws text help content
        void DrawHelp();
        ///returns the biggest side of the screen
        static int GetSquareSide();
        static double* GetTransformationMatrix(){return calibration_matrix;}
	private:
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
