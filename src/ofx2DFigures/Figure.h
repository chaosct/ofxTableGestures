#ifndef DFIGURE_H
#define DFIGURE_H

#include "BoundingBox.h"
#include <string>
#include "ofMain.h"

class Figure
{
    public:
        Figure();
        virtual ~Figure();
        void SetTexture(const std::string & path);
        void SetTexture(ofImage& image);
    protected:
        BoundingBox bbox;
        bool has_texture;
        ofImage texture;
    private:
};

#endif // DFIGURE_H
