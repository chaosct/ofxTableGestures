#ifndef _LINE_HPP_
#define _LINE_HPP_

// Still, weird things in last vertex...

#include <vector>
#include "Graphic.hpp"
#include "ofVbo.h"

namespace tableGraphics{
    class Line : public Graphic{
        public:
            Line(int resolution = 0);
            void clear();

        // Set resolution used to draw waveforms and arcs.
            void setResolution(int r = 0);

        // Waveform is updated interpolating the input vector values.
            void updateWaveform(std::vector<float>&, float amplitude = 1);

        // Generate an arc. Percent = 100 renders a circular shape.
            void setArc(float percent = 100);

            void setEndpoints(const ofVec2f&, const ofVec2f&);
            void draw();

        private:
            ofVbo vbo;
            ofMatrix4x4 matrix;
            std::vector<ofVec3f> normals;
            unsigned int size;

            void setData(const std::vector<ofVec3f>& vertices,
                         const std::vector<ofVec3f>& normals);
    };
}

#endif // _LINE_HPP_

