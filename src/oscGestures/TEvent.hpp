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

#ifndef TUIO_TEVENT_H
#define TUIO_TEVENT_H



#include <vector>
#include <iostream>
#include "Singleton.hpp"



namespace tuio {

///This class assigns a single identifier to every TEvent subclass
class EventTypes : public Singleton<EventTypes>
{
    private:
    unsigned int n;
    protected:
    friend class Singleton<EventTypes>;
    EventTypes():n(0){}
    public:
    template<typename T>
    unsigned int get_number()
    {
        static bool ins = false;
        static unsigned int uniquename;
        if (!ins)
        {
            uniquename = n++;
            ins = true;
        }
        return uniquename;
    }
};


///Base class for all TEvents
class TEvent {
  public:
      unsigned int name;
#ifdef DEBUG
      std::string debugName;
#endif
    TEvent(){}

};


} // namespace tuio


#endif
