#include "CollisionHelper.h"

Figures::Matrix Figures::CollisionHelper::ignore_transformation_matrix = Matrix();

bool Figures::CollisionHelper::debug_graphics = false;

namespace Figures
{
    void SetColor (ofColor color)
    {
        ofSetColor(color.r, color.g, color.b, color.a);
    }

    unsigned int parseHexColor(std::string & color)
    {
        unsigned int toreturn;
        std::stringstream ss;
        if(color.size() <= 6)color+="FF";
        ss << std::hex << color;
        ss >> toreturn;
        return toreturn;
    }

    void Get_rgb_from_hex(std::string & color, int &red, int &green, int &blue, int &alpha)
    {
        unsigned int hexColor = parseHexColor(color);
        red = (hexColor >> 24) & 0xff;
        green = (hexColor >> 16) & 0xff;
        blue = (hexColor >> 8) & 0xff;
        alpha = (hexColor >> 0) & 0xff;
    }

    ofColor GetColorFromString(std::string color)
    {
        int r,g,b,a;
        Get_rgb_from_hex(color, r, g, b, a);
        ofColor clr;
        clr.r = r;
        clr.g = g;
        clr.b = b;
        clr.a = a;
        return clr;
    }
}
