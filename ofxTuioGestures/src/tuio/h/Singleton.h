#ifndef SINGLETON_H
#define SINGLETON_H
//Inspired by http://cc.byexamples.com/20080609/stl-singleton-template/

template<typename T>
class Singleton
{
    public:
        static T& Instance()
        {
            static T me;
            return me;
        }
        static T* get()
        {
            return &Instance();
        }
};

#endif //SINGLETON_H
