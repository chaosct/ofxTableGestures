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

#include "Polygon.h"
#include "CollisionHelper.h"

using namespace Figures;
using namespace std;

Polygon::Polygon()
{

}

Polygon::Polygon(vector_points):processed(false),it_is_empty(true)
{
    centre = ofPoint(-1.0,-1.0);
}

void Polygon::AddVertex(ofPoint vertex)
{
    raw_vertexs.push_back(vertex);
    bbox.AddPoint(vertex.x,vertex.y);
    if(it_is_empty)
    {
        centre = ofPoint(vertex);
    }
    else
    {
        centre += vertex;
        centre = centre / 2;
    }
    processed = false;
}

void Polygon::RebuildGeometry()
{
    if(raw_vertexs.size() >= 3)
    {
        updatedVertexs.clear();
        for(unsigned int i = 0; i < raw_vertexs.size(); i++)
            updatedVertexs.push_back(ofPoint(raw_vertexs[i]));
        SetUpdatedPolygonVertices();
        CutEars();
        processed = true;
    }
}

void Polygon::SetUpdatedPolygonVertices()
{
    //updatedVertexs should be in count clock wise
    if (CollisionHelper::PointsDirection(updatedVertexs) == Clockwise)
        CollisionHelper::ReversePointsDirection(updatedVertexs);
}

void Polygon::CutEars()
{
    bool is_finished = false;
    if (updatedVertexs.size() == 3)
        is_finished = true; //it is a triangle!!
    ofPoint pt = ofPoint(0,0);
    while (is_finished == false)
    {
        unsigned int i = 0;
        bool not_found = true;
        while (not_found && i < updatedVertexs.size())
        {
            pt = updatedVertexs[i];
            if (IsEarOfUpdatedPolygon(pt))
                not_found = false;
            else i++;
        }
        if (pt.x != -999)
        {
            UpdatePolygonVertices(pt);
        }
        if (updatedVertexs.size() == 3)
            is_finished = true;
    }
    SetPolygons();
}

bool Polygon::IsEarOfUpdatedPolygon(ofPoint const & vertex)
{
    if (IsPartOfUpdatedVertexs(vertex))
    {
        bool bEar = true;
        if (PolygonVertexType_on_UpdatedVertexs(vertex) == ConvexPoint)
        {
            ofPoint pi = vertex;
            ofPoint pj = PreviousUpdatedVertexs(vertex);
            ofPoint pk = NextUpdatedVertexs(vertex);

            //for (int i = updatedVertexs.GetLowerBound(0);i < updatedVertexs.GetUpperBound(0); i++)
            for (unsigned int i = 0;i < updatedVertexs.size(); i++)
            {
                ofPoint pt = updatedVertexs[i];
                if (!(CollisionHelper::SamePoints(pt, pi) ||
                    CollisionHelper::SamePoints(pt, pj) ||
                    CollisionHelper::SamePoints(pt, pk)))
                {
                    if (CollisionHelper::CollideTriangle(pj, pi, pk, pt.x, pt.y))
                    {
                        bEar = false;
                    }
                }
            }
        }
        else  //concave point
            bEar = false; //not an ear/
        return bEar;
    }
    return false;
}

bool Polygon::IsPartOfUpdatedVertexs(ofPoint const & vertex)
{
    for(unsigned int i = 0; i < updatedVertexs.size(); i++ )
    {
        if( CollisionHelper::SamePoints(updatedVertexs[i],vertex))
            return true;
    }
    return false;
}

int Polygon::VertexIndex_of_UpdatedVertexs(ofPoint const & vertex)
{
    int nIndex = -1;
    int nNumPts = updatedVertexs.size();
    for (int i = 0; i < nNumPts; i++) //each vertex
    {
        if (CollisionHelper::SamePoints(updatedVertexs[i], vertex))
            nIndex = i;
    }
    return nIndex;
}

ofPoint Polygon::PreviousUpdatedVertexs(ofPoint const & vertex)
{
    int nIndex;
    nIndex = VertexIndex_of_UpdatedVertexs(vertex);
    if (nIndex == -1)
        return ofPoint(-1,-1);
    else //a valid vertex
    {
        if (nIndex == 0) //the first vertex
        {
            return updatedVertexs[updatedVertexs.size() - 1];
        }
        else //not the first vertex
            return updatedVertexs[nIndex - 1];
    }
}

ofPoint Polygon::NextUpdatedVertexs(ofPoint const & vertex)
{
    int nIndex;
    nIndex = VertexIndex_of_UpdatedVertexs(vertex);
    if (nIndex == -1)
        return ofPoint(-999, -999);
    else //a valid vertex
    {
        if (nIndex == (int)updatedVertexs.size() - 1) //the last vertex
        {
            return updatedVertexs[0];
        }
        else //not the last vertex
            return updatedVertexs[nIndex + 1];
    }
}

PolyVertexType Polygon::PolygonVertexType_on_UpdatedVertexs(ofPoint const & vertex)
{
    PolyVertexType vertexType = ErrorPoint;
    if (IsPartOfUpdatedVertexs(vertex))
    {
        /*ofPoint pti = vertex;
        ofPoint ptj = PreviousUpdatedVertexs(vertex);
        ofPoint ptk = NextUpdatedVertexs(vertex);*/

        vector_points triangle;
        triangle.push_back(ofPoint(vertex));
        triangle.push_back(ofPoint(PreviousUpdatedVertexs(vertex)));
        triangle.push_back(ofPoint(NextUpdatedVertexs(vertex)));

        double dArea = CollisionHelper::PolygonArea(triangle);

        if (dArea < 0)
            vertexType = ConvexPoint;
        else if (dArea > 0)
            vertexType = ConcavePoint;
    }
    return vertexType;
}

void Polygon::UpdatePolygonVertices(ofPoint const & vertex)
{
    vector_points alTempPts;
    alTempPts.clear();

    for (unsigned int i = 0; i < updatedVertexs.size(); i++)
    {
        if (CollisionHelper::SamePoints(vertex,updatedVertexs[i])) //add 3 pts to FEars
        {
            /*Vector2 pti = vertex;
            Vector2 ptj = PreviousUpdatedVertexs(vertex); //previous point
            Vector2 ptk = NextUpdatedVertexs(vertex); //next point

            Vector2[] aEar = new Vector2[3]; //3 vertices of each ear
            aEar[0] = ptj;
            aEar[1] = pti;
            aEar[2] = ptk;*/

            vector_points triangle;
            triangle.push_back(ofPoint(vertex));
            triangle.push_back(ofPoint(PreviousUpdatedVertexs(vertex)));
            triangle.push_back(ofPoint(NextUpdatedVertexs(vertex)));

            m_alEars.push_back(triangle);
        }
        else
        {
            alTempPts.push_back(updatedVertexs[i]);
        } //not equal points
    }

    if (updatedVertexs.size() - alTempPts.size() == 1)
    {
//        int nLength = updatedVertexs.size();
        updatedVertexs.clear();// = new Vector2[nLength - 1];

        for (unsigned int i = 0; i < alTempPts.size(); i++)
            updatedVertexs.push_back(ofPoint(alTempPts[i]));
    }

}

void Polygon::SetPolygons()
{
    int nPolygon = m_alEars.size() + 1; //ears plus updated polygon
    triangles.clear();

    for (int i = 0; i < nPolygon - 1; i++) //add ears
    {
        triangles.push_back(vector_points());
        triangles[i].push_back(ofPoint(m_alEars[i][0]));
        triangles[i].push_back(ofPoint(m_alEars[i][1]));
        triangles[i].push_back(ofPoint(m_alEars[i][2]));
    }

    //add UpdatedPolygon:
    triangles.push_back(vector_points());

    for (unsigned int i = 0; i < updatedVertexs.size(); i++)
    {
        triangles[nPolygon - 1].push_back(updatedVertexs[i]);
    }
}

int Polygon::GetTriangleNumber()
{
    if (!processed) RebuildGeometry();
    return triangles.size();
}

void Polygon::Design()
{
    if (!processed) RebuildGeometry();
}

void Polygon::DesignStroke()
{
    if (!processed) RebuildGeometry();
}

bool Polygon::CheckCollision(ofPoint const & point)
{
    if (!processed) RebuildGeometry();
    return false;
}

void Polygon::GetCentre(float & x, float & y)
{
    x = centre.x;
    y = centre.y;
}

