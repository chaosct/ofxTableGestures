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

#ifndef TUIO_EVENTQUEUE_H
#define TUIO_EVENTQUEUE_H


#include "TEvent.hpp"
#define QUEUE_SIZE 1024

namespace tuio
{

template <typename T,int size, bool discardDuplicates = true>
class blocklessQueue
{
private:
    T * events[size];

    unsigned int reader;
    unsigned int writer;

public:
    blocklessQueue():reader(0),writer(0)
    {
        ///Filling queue with NULL
        for (int i = 0; i < size; ++i)
            events[i]=NULL;
    }
    void push(T * evt)
    {
        if(evt == NULL)
        {
            std::cout << "WARNING: Queue discarding NULL item." << std::endl;
            return;
        }
        if(discardDuplicates)
        {
            for (unsigned int i = reader; i != writer; i = (i + 1)%size)
                if(events[i]==evt)
                {
                    //std::cout << "WARNING: Queue discarding duplicated item." << std::endl;
                    return;
                }
        }
        if( (writer +1)%size ==  reader)
        {
            ///discard messages when full
            std::cout << "WARNING: Queue Full: discarding element." << std::endl;
            delete evt;
            return;
        }
        events[writer]=evt;
        writer = (writer + 1)%size;
    }

    T * pop()
    {
        if( reader ==  writer)
        {
            return NULL; // return NULL when empty
        }
        T * evt = events[reader];
        reader = (reader + 1)%size;
        return evt;
    }

};

///We do not need to check for duplicate items in the event queue.
typedef blocklessQueue<TEvent,QUEUE_SIZE,false> EventQueue;

} // namespace tuio
#endif
