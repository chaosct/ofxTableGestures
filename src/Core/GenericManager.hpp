#ifndef _GENERIC_MANAGER_H_
#define _GENERIC_MANAGER_H_

class GenericManager{
    public:
        ~GenericManager();
        void initAll();

        template<typename Type>
        static Type* get(){
            static Type* gesture = new Type();
            return gesture;
        }
};

#endif // _GENERIC_MANAGER_H_

