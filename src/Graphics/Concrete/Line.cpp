#include "Line.hpp"
#include "ofxGlobalConfig.hpp" // Shader paths
#include "ofPolyline.h" // Auxiliar ofPolyline in setArc()

using namespace tableGraphics;

//// Default shaders ////
static const string vertShader = "\
    #version 110 \n\
    varying vec4 color; \n\
    void main(){ \n\
	color = gl_Color; \n\
        vec4 waveform = gl_Vertex + vec4(gl_Normal.xy, 0, 0) * gl_Normal.z; \n\
        gl_Position = gl_ModelViewProjectionMatrix * waveform; \n\
    }";

static const string fragShader = "\
    #version 110 \n\
    varying vec4 color; \n\
    void main(){ \n\
        gl_FragColor = color; \n\
    }";
/////////////////////////

Line::Line(int r){
    setResolution(r);
    ofVec2f init(0);
    setEndpoints(init, init);
}

void Line::clear(){
    std::vector<ofVec3f> nullLine;
    nullLine.push_back(ofVec3f(0));
    setData(nullLine, nullLine);
}

void Line::setResolution(int res){
    if (res <= 2){
        size = 2;
    }else{
        size = res;
        const string& shaderPath = ofxGlobalConfig::getRef("FIGURE:LINE:SHADER", string("shaders/line"));
        loadShader(shaderPath, vertShader, fragShader);
    }
    ofVec3f normal(0, -1, 0);
    normals.clear();
    std::vector<ofVec3f> waveform;
    for (unsigned int i = 0; i < size; ++i) {
        ofVec3f vertex(i/(float)size-0.5f, 0);
        waveform.push_back(vertex);
        normals.push_back(normal);
    }
    normals.push_back(normal);
    setData(waveform, normals);
}

void Line::setEndpoints(const ofVec2f& pA, const ofVec2f& pB){
    ofVec2f pos = pB - pA;
    float length = sqrt(pow(pos.x, 2) + pow(pos.y, 2));
    float angle = atan2(pos.y, pos.x) * 180/PI;
    pos = pos / 2 + pA;

    matrix.makeIdentityMatrix();
    matrix.scale(length, length, 1);
    matrix.rotate(angle, 0, 0, 1);
    matrix.translate(pos.x, pos.y, 0);
}

void Line::updateWaveform(std::vector<float>& input, float amplitude){
    unsigned int vertsCount = vbo.getNumVertices();
    amplitude *= 0.5f / matrix.getScale().y;
    float increment = input.size() / (float)vertsCount;
    input.push_back(0.0f); // Prevent off-by-1 on input[step + 1]
    for(unsigned int i = 0; i < vertsCount; ++i){
        unsigned int step = i * increment;
        float interp = i * increment - step;
        float value = input[step] * (1-interp);
        value += input[step + 1] * interp;

        // Hann-window both extremes ([0%-10%] and [90%-100%] of total length)
        float window = 1.0f;
        float pos = i / (float)vertsCount;
        if(pos < 0.1f || pos > 0.9f){
            window = 0.5f * (1 - cos(PI * pos / 0.1f));
        }
        normals[i].z = value * amplitude * window;
    }
    input.pop_back(); // Revert to original input vector
    vbo.updateNormalData(&normals[0], normals.size());
}

void Line::setArc(float arc){
    if(arc == 0){
        // Generate a straight line
        setResolution(size);
        return;
    }
    // Compute arc from an auxiliar ofPolyline.
    //   Note that isn't as optimum as would be an ad hoc solution.
    ofPolyline auxLine;
    float centerDist = log10(100/abs(arc));
    float radius = sqrt(pow(centerDist, 2) + pow(0.5f, 2));
    if(arc < 0) {
        // Reverse direction
        centerDist *= -1;
        radius *= -1;
    }
    float angle = acos(centerDist/radius) * 180/PI;
    int vertices = size * 180/angle;
    auxLine.arc(0, centerDist, radius, radius, 270-angle, 270+angle, vertices);
    vector<ofVec3f> result = auxLine.getVertices();

    // Compute normals
    normals.clear();
    normals.push_back(ofVec3f(0));
    for(vector<ofVec3f>::iterator it = ++result.begin(); it != --result.end(); ++it){
        ofVec3f normal(*it - ofVec2f(0, centerDist));
        normals.push_back(normal.normalize());
    }
    normals.push_back(ofVec3f(0));

    setData(result, normals);
}

void Line::draw() {
    ofPushMatrix();
    ofMultMatrix(matrix);
    vbo.draw(GL_LINE_STRIP, 0, vbo.getNumVertices());
    ofPopMatrix();
}

void Line::setData(const std::vector<ofVec3f>& vertices, \
                   const std::vector<ofVec3f>& normals){
    int usage = size > 2 ? GL_STREAM_DRAW : GL_STATIC_DRAW;
    vbo.setVertexData(&vertices[0], vertices.size(), usage);
    vbo.setNormalData(&normals[0], normals.size(), usage);
}

