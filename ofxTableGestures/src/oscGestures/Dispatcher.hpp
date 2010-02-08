/*

    OF-TangibleFramework . Framework for Taller de Sistemes Interactius I
    Universitat Pompeu Fabra

    Copyright (c) 2009 Daniel Gallardo Grassot <daniel.gallardo@upf.edu>

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

#ifndef DISPATCHER_H_INCLUDED
#define DISPATCHER_H_INCLUDED

#include "tuioApp.h"
#include "Listener.h"

namespace tuio
{

    ///This class stores an instance of all Listenenrs and distribute the generated events
    class Dispatcher :public Singleton< Dispatcher >
    {
        private:
            ///List where all Listeners will be stored
            std::list<Listener*> listeners_list;
            ///queue of generated events
            EventQueue * equeue;
        protected:
            friend class Singleton< Dispatcher >;
            ///Dispatcher()
            ///Constructor, it starts the tuioinput thread (if not started) and recuperates the eventqueue
            Dispatcher(){
                Singleton<tuio::tuioinput>::Instance().init();
                equeue = Singleton<tuio::tuioinput>::Instance().getQueue();
            }
        public:
            ///void AddListener(Listener* listener)
            ///outputs:none
            ///inputs:
            ///     Listener* listener -> pointer to a listener.
            ///Desc: Adds a listener to listeners_list
            void AddListener(Listener* listener){
                listeners_list.push_back(listener);
            }
            ///void RemoveListener(Listener* listener)
            ///outputs:none
            ///inputs:
            ///     Listener* listener -> pointer to a listener.
            ///Desc: Removes a Listener from listeners_list
            void RemoveListener(Listener* listener){
                listeners_list.remove(listener);
            }
            ///void processTevents();
            ///outputs: none
            ///inputs: none
            ///Desc: foreach event stored into the eventqueue executes the
            ///process event of each Listener stored into listeners_list
            void processTevents();
            ///void tostring();
            ///outputs: none
            ///inputs: none
            ///Desc: shows at stdoutput the number of listeners added
            void tostring();

    };
}

#endif // DISPATCHER_H_INCLUDED
