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

#include <queue>
#include "autoGraphic.hpp"
#include "InputGestureTap.hpp"

class TapFeedback : public EventClient{
    public:
        TapFeedback();
        void Tap(InputGestureTap::TapArgs&);

        class CircleTap : public FeedbackGraphic{
            public:
                CircleTap(const ofVec2f& position, float maxradius, float lifeTime);
                float getBornTime();
                void draw();
                void clear(){}

            private:
                float born;
                float lifetime;
                float maxradius;
                ofVec2f p;
        };

    private:
        float& lifetime;
        float& maxradius;
        std::queue<CircleTap*> taps;
};

#endif // TAPFEEDBACK_HPP_INCLUDED
