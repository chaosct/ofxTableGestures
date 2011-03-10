#include "Figure.h"

Figure::Figure():has_texture(false)
{
    //ctor
}

Figure::~Figure()
{
    //dtor
}

void Figure::SetTexture(const std::string & path)
{
    if (path.compare("") == 0)
    {
        has_texture = false;
        return;
    }
    texture.loadImage(path);
    has_texture = true;
}

void Figure::SetTexture(ofImage& image)
{
    if(image.getHeight() == 0)
    {
        has_texture = false;
        return;
    }
    texture = image;
    has_texture = true;
}
