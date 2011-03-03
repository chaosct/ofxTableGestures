/*

    ofxTableGestures (formerly OF-TangibleFramework)
    Developed for Taller de Sistemes Interactius I
    Universitat Pompeu Fabra

    Copyright (c) 2010 Carles F. Julià <carles.fernandez@upf.edu>

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

#ifndef TAPFEEDBACK_HPP_INCLUDED
#define TAPFEEDBACK_HPP_INCLUDED

#include "InputGestureTap.hpp"
#include "Graphic.hpp"

class TapFeedback : public CanTap < Graphic >
{
    float & lifetime;
    float & maxradius;
    public:
    class CircleTap : public Graphic
    {
        float born;
        float lifetime;
        float maxradius;
        DirectPoint p;
        public:
        CircleTap(const DirectPoint & dp, float r, float lt):
        p(dp),
        maxradius(r),
        lifetime(lt),
        born(ofGetElapsedTimef()){}
        void update()
        {
            float now = ofGetElapsedTimef();
            if(now - born > lifetime)
                delete this;
        }
        void draw()
        {
            static int & R = GlobalConfig::getRef("FEEDBACK:CURSOR:COLOR:R",255);
            static int & G = GlobalConfig::getRef("FEEDBACK:CURSOR:COLOR:G",0);
            static int & B = GlobalConfig::getRef("FEEDBACK:CURSOR:COLOR:B",0);

            float now = ofGetElapsedTimef();
            float alpha = ((now - born) / lifetime);
            float radius = alpha * maxradius ;
            int alpha255 = (int)((1.0f-alpha)*255);
            ofPushStyle();
            ofNoFill();
            ofSetLineWidth(4);
            ofSetColor(R,G,B,alpha255);
            ofEnableAlphaBlending();
            ofCircle(p.getX(),p.getY(),radius);
            ofDisableAlphaBlending();
            ofPopStyle();
        }
    };

    TapFeedback(Area * a = NULL):
    lifetime(GlobalConfig::getRef("FEEDBACK:TAP:DURATION",1.0f)),
    maxradius(GlobalConfig::getRef("FEEDBACK:TAP:MAXRADIUS",0.1f))
    {
//        Register(a);
    }

    void Tap(float x, float y)
    {
        new CircleTap(DirectPoint(x,y),maxradius,lifetime);
    }
};

#endif // TAPFEEDBACK_HPP_INCLUDED
