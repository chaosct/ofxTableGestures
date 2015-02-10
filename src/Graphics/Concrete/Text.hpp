#ifndef _TEXT_HPP_
#define _TEXT_HPP_

#include <string>
#include "ofTrueTypeFont.h"
#include "ofxGlobalConfig.hpp"
#include "Graphic.hpp"

namespace tableGraphics{
    class Text : public Graphic{
        public:
            Text();
            bool collide(const ofPoint&);

            // Font is loaded with a default size of 10 at construction, but
            //   it must be reloaded if ignoreStackMatrix() it's called.
            void loadFont(int size, string font = "");
            void draw();
            void clear();
            void useGlobalSize(bool);

            template<typename T>
            Text& operator <<(T& input){
                text << input;
                return *this;
            }
            template<typename T>
            Text& operator <<(const T& input){
                text << input;
                return *this;
            }
            typedef std::basic_ostream<char, std::char_traits<char> > CoutType;
            typedef CoutType& (*stdEndl)(CoutType&);
            Text& operator <<(stdEndl f){
                f(text);
                return *this;
            }

        private:
            ofTrueTypeFont font;
            std::stringstream text;
            float scaling;
            float& globalSize;
            bool usingGlobalSize;
    };
}

#endif // _TEXT_HPP_

