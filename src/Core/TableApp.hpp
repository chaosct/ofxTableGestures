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
#include <string>
#include "GenericManager.hpp"
#include "OscInput.hpp"
#include "OnlySimulator.h"

#ifdef ONLY_SIMULATOR
#undef NO_SIMULATOR
#endif //ONLY_SIMULATOR

class Grid;
class Renderer;
namespace tableGraphics{
    class Text;
}

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
        GenericManager genericManager;
        OscInput oscInput;

        ///Global matrix
        ofMatrix4x4 matrix;

        ///Renderer: used for distortionate the graphic output.
        Renderer *renderer;

        ///Grid: used for drawing the calibration grid on the screen.
        Grid* grid;
        bool show_grid;
	/// selector of calibration parameter
	/// translate, rotate, scale, rotate x and y axes,...
        int calibration_mode;

        ///Help text
        tableGraphics::Text* helpText;
        bool show_help;

        ///Graphic information text
        tableGraphics::Text* infoText;
        bool show_info;

        ///Show/hide cursor flag
        bool hide_cursor;

        ///Simulator
#ifndef NO_SIMULATOR
        simulator::Simulator* simulator;
        ///distortion status before enable simulator.
        bool was_distorsion_enabled;
        ///cursor status before enable simulator.
        bool was_cursor_hide;
#endif
        ///App Window Name
        std::string win_name;

        ///Cursor key evaluation
        void Evaluate_Cursor(int key);

	///Update global matrix
	void updateMatrix(const ofVec2f& winSize);

        void toggleSimulator();

    public:
        ///Constructor, here is initialized all data
        ///and loaded distortion parameters from file.
        TableApp(std::string name = "Table APP");
        ///Destructor
        virtual ~TableApp();

        /// Screen information
        void loadInfo();
        void updateInfo();

        /// Help content
        void loadHelp();

        ///returns the biggest side of the screen
        static int GetSquareSide();

        ///Key funcs, they only repports the ones that are not used by the system
        virtual void KeyPressed  (int){}
        virtual void KeyReleased (int){}

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
};

#endif
