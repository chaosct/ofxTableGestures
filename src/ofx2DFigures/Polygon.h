/*

    ofxTableGestures (formerly OF-TangibleFramework)
    Developed for Taller de Sistemes Interactius I
    Universitat Pompeu Fabra

    Copyright (c) 2011 Daniel Gallardo Grassot <daniel.gallardo@upf.edu>

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

#ifndef POLYGON_H
#define POLYGON_H

#include "Figure.h"
#include "CollisionHelper.h"

namespace Figures
{
    class Polygon : public Figure
    {
        public:
            Polygon();
            Polygon(vector_points);
            void AddVertex(ofPoint vertex);
        protected:
            /// Vertexs of the polygon.
            vector_points raw_vertexs;
            /// Flag that says if all vertexs has been processed.
            bool processed;
            /// vertexs to be processed by the cutting ears algorythm.
            vector_points updatedVertexs;
            /// <summary>
            /// cutted ears temporary list.
            /// </summary>
            //private System.Collections.ArrayList m_alEars = new System.Collections.ArrayList();
            /// Subdivision in triangles of the polygon.
            std::vector<vector_points> triangles;
            /// centre of th polygon.
            ofPoint centre;

            virtual void RebuildGeometry();
            virtual void Design();
            virtual void DesignStroke();
            virtual bool CheckCollision(ofPoint const & point);
            virtual void GetCentre(float & x, float & y);
    };
}
#endif // POLYGON_H
