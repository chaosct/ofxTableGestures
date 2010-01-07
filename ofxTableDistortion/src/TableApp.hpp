/*
* Daniel Gallardo Grassot
* daniel.gallardo@upf.edu
* Universitat Pompeu Fabra
* Music Technology Group
*/

#ifndef _TABLE_APP
#define _TABLE_APP

#include "ofMain.h"
#include "Grid.hpp"

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
    public:
        TableApp();
        virtual void Setup()=0;
        virtual void Update()=0;
        virtual void Draw()=0;
        virtual void WindowResized(int w, int h)=0;
        void SaveDistortion();
        void LoadDistortion();
        void DrawInfo();
        void DrawHelp();
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
