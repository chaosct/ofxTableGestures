/*
* Daniel Gallardo Grassot
* dgallardo@iua.upf.edu
* Universitat Pompeu Fabra
* Music Technology Group
*/

#ifndef _GRID
#define _GRID

class Grid{
    private:
        /// opengl list index
        int grid_list;
        int arrows_list;
        int w_lines;
        int h_lines;
    public:
        Grid(int _w_lines, int _h_lines);
        ~Grid();
        void Draw(bool calibration_enabled, int calibration_mode);
        void Resize();
    private:
        void GenerateOpenGL_lists();
        void RenderArrow_one(int size);
        void RenderArrow_two(int size);
        void DrawArrow_three(int size);
};

#endif
