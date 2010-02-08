/*

    OF-TangibleFramework . Framework for Taller de Sistemes Interactius I
    Universitat Pompeu Fabra

    Copyright (c) 2009 Carles F. Julià <carles.fernandez@upf.edu>

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
#include "Singleton.h"

namespace tuio {

///This class assigns a single identifier to every TTEvent subclass
class EventTypes : public Singleton<EventTypes>
{
    private:
    unsigned int n;
    protected:
    friend class Singleton<EventTypes>;
    EventTypes():n(0){}
    public:
    unsigned int getNumber()
    {
        return n++;
    }
};


///Base class for all TEvents
class TEvent {
  public:
      unsigned int name;
    TEvent(){}

};


///The TTEvent template class allows every TEvent subclass to get a single differenciate identifier.
template <typename TE>
class TTEvent : public TEvent
{
    public:
    TTEvent()
    {
        static bool ins = false;
        static unsigned int uniquename;
        if (!ins)
        {
            uniquename = EventTypes::Instance().getNumber();
            ins = true;
        }
        name = uniquename;
    }
};


} // namespace tuio


#endif
