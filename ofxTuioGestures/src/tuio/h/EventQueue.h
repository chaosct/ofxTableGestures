/*

    TSIframework . Framework for Taller de Sistemes Interactius I
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

#ifndef TUIO_EVENTQUEUE_H
#define TUIO_EVENTQUEUE_H


#include "TEvent.h"

#define QUEUE_SIZE 1024

namespace tuio
{

template <typename T,int size>
class blocklessQueue
{
private:
    T * events[size];

    unsigned int reader;
    unsigned int writer;

public:
    blocklessQueue():reader(0),writer(0) {}
    void push(T * evt)
    {
        if( (writer +1)%QUEUE_SIZE ==  reader)
        {
            //discard messages when full
            std::cout << "Event Queue Full: discarding event :" << evt->name << std::endl;
            delete evt;
            return;
        }
        events[writer]=evt;
        writer = (writer + 1)%QUEUE_SIZE;
    }

    T * pop()
    {
        if( reader ==  writer)
        {
            return NULL; // return NULL when empty
        }
        TEvent * evt = events[reader];
        reader = (reader + 1)%QUEUE_SIZE;
        return evt;
    }

};

typedef blocklessQueue<TEvent,QUEUE_SIZE> EventQueue;

} // namespace tuio
#endif
