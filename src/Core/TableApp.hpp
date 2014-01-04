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

#ifndef _TABLE_APP
#define _TABLE_APP

#include "ofMain.h"
#include "Grid.hpp"
#include "Renderer.hpp"
#include <string>

///By defining the global "NO_SIMULATOR", it disables the integrated simulator.
///When it is enabled, it can be activated by tapping the 's' key.
#ifndef NO_SIMULATOR
    #include "Simulator.hpp"
#else
    #warning Simulator disabled
#endif

///Table App is an interface class to deal with all table calibration processes, simulator mode and
///abstractize the dispatchers from the main aplication of this project
class TableApp {
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
		#ifndef NO_SIMULATOR
            simulator::Simulator* simulator;
            ///Simulator enabled flag
            bool is_simulating;
            ///distortion status before enable simulator.
            bool was_distorsion_enabled;
            ///cursor status before enable simulator.
            bool was_cursor_hide;
        #endif
//        static double* calibration_matrix;
        int & squaredInterface;

        ///Flag to recalculate the ignore collision matrix.
        bool matrix_updated;
        //App Window Name
        std::string win_name;
    public:
        ///Constructor, here is initialized all data
        ///and loaded distortion parameters from file.
    TableApp(std::string name = "Table APP");
        ///Destructor
        ~TableApp();

        /// Draws text screen information
        void DrawInfo();
        /// Draws text help content
        void DrawHelp();
        ///returns the biggest side of the screen
        static int GetSquareSide();
//        static double* GetTransformationMatrix(){return calibration_matrix;}
        ///Key funcs, they only repports the ones that are not used by the system
        virtual void KeyPressed  (int key){}
		virtual void KeyReleased (int key){}

        /// ofBaseApp methods..
		void setup();
		void update(ofEventArgs & args);
		void draw();
		void keyPressed  (ofKeyEventArgs & event);
		void keyReleased(ofKeyEventArgs & event);
		void mouseDragged(ofMouseEventArgs & event);
		void mousePressed(ofMouseEventArgs & event);
		void mouseReleased(ofMouseEventArgs & event);
		void windowResized(ofResizeEventArgs & event);

		///From old GlobalConfig
		static float height;
		static float width;
        static float getHeight(){return TableApp::height;}
        static float getWidth(){return TableApp::width;}

};

#endif
