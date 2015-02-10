/*

    ofxTableGestures (formerly OF-TangibleFramework)
    Developed for Taller de Sistemes Interactius I
    Universitat Pompeu Fabra

    Copyright (c) 2010 Daniel Gallardo Grassot <daniel.gallardo@upf.edu>

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

#ifndef _GRAPHIC_DISPATCHER_H_
#define _GRAPHIC_DISPATCHER_H_
#include <list>

#include "ofLog.h"
#include "ofPoint.h"
#include "ofUtils.h" // ofGetElapsedTimef()

#define BGR_LAYER 0
#define APP_LAYER 100
#define NOT_LAYER 200

class Graphic;

class GraphicDispatcher{
    public:
        //! Creates new graphic.
        /*!
           \param newGraphic pointer to graphic.
           \param layer layer of the new graphic.
           \return No return value, newGraphic will be pointing to the new graphic.
        */
        template <class graphicType>
        void createGraphic(graphicType*& newGraphic, int layer = APP_LAYER) {
            newGraphic = new graphicType;
            layeredGraphic newLayered = { newGraphic,
                                          std::make_pair(layer, ofGetElapsedTimef()) };
            graphics.push_back(newLayered);
            graphics.sort();
        }

        template <class graphicType>
        graphicType* copyGraphic(const graphicType* source){
            GraphicsList::iterator it = std::find(graphics.begin(), graphics.end(), source);
            if(it == graphics.end()){
                ofLogError("GraphicDispatcher::duplicateGraphic") << "Graphic not found";
                return NULL;
            }
            graphicType* copied = new graphicType(*dynamic_cast<graphicType*>(it->graphic));
            layeredGraphic newLayered = { copied,
                                          std::make_pair(it->layer.first, ofGetElapsedTimef()) };
            graphics.push_back(newLayered);
            graphics.sort();
            return copied;
        }

        //! Removes a graphic.
        /*!
           \param graphic pointer to graphic.
           \return Pointer to NULL if succeed.
        */
        Graphic* removeGraphic(Graphic*);

        //! Draws all graphics.
        void Draw();

        //! Check if point is colliding with some graphic.
        /*!
           \param point reference to a ofPoint object.
           \return Pointer to colliding graphic, or NULL otherwise.
           \sa ofPoint, ofVec3f.
        */
        Graphic* Collide(const ofPoint& point);

        //! Set graphic's layer
        /*!
           \param newLayer layer number.
           \param graphic pointer to graphic.
           \sa bringTop(Graphic*)
        */
        void setLayer(int newLayer, Graphic* graphic);

        //! Bring graphic to top of the current layer.
        /*!
           \param graphic pointer to graphic.
           \sa setLayer(Graphic*, int)
        */
        void bringTop(Graphic* graphic);

    private:
        struct layeredGraphic {
            Graphic* graphic;
            std::pair<int, float> layer;

            bool operator < (const layeredGraphic& rhs) const {
                return layer < rhs.layer;
            }
            bool operator == (const Graphic* rhs) const {
                return graphic == rhs;
            }
        };

        typedef std::list<layeredGraphic> GraphicsList;
        GraphicsList graphics;
};

#endif //_GRAPHIC_DISPATCHER_H_
