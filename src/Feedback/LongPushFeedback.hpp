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

#ifndef KEEPFEEDBACK_HPP_INCLUDED
#define KEEPFEEDBACK_HPP_INCLUDED

#include "InputGestureLongPush.hpp"
#include "Graphic.hpp"

class LongPushFeedback : public CanLongPush < Graphic >
{
    float & lifetime;
    float & maxradius;
    public:
    class CircleTap : public NotificationGraphic
    {
        float born;
        float lifetime;
        float maxradius;
        ofVec2f p;

        public:

        CircleTap(const ofVec2f& dp, float r, float lt):
            born(ofGetElapsedTimef()),
            lifetime(lt),
            maxradius(r),
            p(dp) {}

        void update()
        {
            float now = ofGetElapsedTimef();
            if(now - born > lifetime)
                delete this;
        }
        void draw()
        {
            float now = ofGetElapsedTimef();
            float alpha = ((now - born) / lifetime);
            float radius = alpha * maxradius ;
            int alpha255 = (int)((1.0f-alpha)*255);
            ofPushStyle();
            ofNoFill();
            ofSetLineWidth(4);
            ofSetColor(255,0,0,alpha255);
            ofEnableAlphaBlending();
            ofCircle(p.x,p.y,radius);
            ofDisableAlphaBlending();
            ofPopStyle();
        }
    };

    LongPushFeedback():
    lifetime(ofxGlobalConfig::getRef("FEEDBACK:TAP:DURATION",1.0f)),
    maxradius(ofxGlobalConfig::getRef("FEEDBACK:TAP:MAXRADIUS",0.1f))
    {
//        Register(a);
    }

    void LongPushTriger(float x, float y)
    {
        new CircleTap(ofVec2f(x,y),maxradius,lifetime);
    }
};

#endif // KEEPFEEDBACK_HPP_INCLUDED
