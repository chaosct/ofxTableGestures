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

#ifndef _RENDERER_TO_TEXTURE
#define _RENDERER_TO_TEXTURE

#include "ofMain.h"
#include "Renderer.hpp"

/**
* After Draw, it stores the output into a texture, aplies some
* translations, rotations and scales to fit the image on the screen.
* It allows draw 3D images without distortionate the ouput on the table.
*/
class Renderer_to_texture : public Renderer{
    private:
        ///Where the graphics output will be sotred
        ofTexture   texScreen;
        ///width and height of the screen.
        int w,h;
    public:
        Renderer_to_texture();
        virtual ~Renderer_to_texture();
        virtual void StartDistortion();
        virtual void EndDistortion();
};

#endif
