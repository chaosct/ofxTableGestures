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

#ifndef SINGLETON_H
#define SINGLETON_H
//Inspired by http://cc.byexamples.com/20080609/stl-singleton-template/

//OK, this is not a REAL singleton, but you get the idea: I just want to avoid repeating code
template<typename T>
class Singleton 
{
    public:
        virtual ~Singleton() {}
        static T& Instance()
        {
            static T me;
            return me;
        }
//        template<typename Arg>
//        static T& Instance(Arg a)
//        {
//            static std::map<Arg,T*> instances;
//            if(instances.find(a) == instances.end()))
//                instances[a] = new T(a);
//            return instances[a];
//        }
        static T& I()
        {
            return Instance();
        }

};

#endif //SINGLETON_H
