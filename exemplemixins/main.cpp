#include <iostream>
#include <list>
#include <string>

using namespace std;

// Define a new mixin class with a constructor that accepts all arguments.

//inspirat per http://www.ddj.com/cpp/184404445
//macros http://en.wikipedia.org/wiki/C_preprocessor

class GenericCallback
{
    public:
    virtual void run()=0;
};

template <class T>
class Callback: public GenericCallback
{
    public:
    Callback(T * i)
    {
        instance = i;
    }
    T * instance ;
    void run()
    {
        //dynamic_cast<T>()
        instance->runme();
    }
};

class Customer
{
public:
    Customer()
    {

    }
    void print()
    {
        list<GenericCallback*>::iterator it;
        for (it = capacitats.begin(); it != capacitats.end(); it++)
        {
            (*it)->run();
        }
    }
    list<GenericCallback*> & getCapacitats()
    {
        return capacitats;
    }
    list<GenericCallback*> capacitats;
};

template <class Base>
class Sapnedar : public Base
{
public:
    Sapnedar()
    {
        cout << "aprenent a nedar" << endl;
        Base::getCapacitats().push_back(new Callback<Sapnedar>(this));
    }
    void runme()
    {
        neda();
    }
    void neda()
    {
        cout << "Nedo" << endl;
    }
    list<GenericCallback*> & getCapacitats()
    {
        return Base::getCapacitats();
    }
};

template <class Base>
class SapCaminar : public Base
{
public:
    SapCaminar()
    {
        cout << "aprenent a caminar" << endl;
        Base::getCapacitats().push_back(new Callback<SapCaminar>(this));
    }
    void runme()
    {
        camina();
    }
    virtual void camina()
    {
        cout << "Camino" << endl;
    }
    list<GenericCallback*> & getCapacitats()
    {
        return Base::getCapacitats();
    }
};
//template <class Base>
class Especialitzacio: public SapCaminar<Sapnedar<Customer> >
{
    public:
    void camina()
    {
        cout << "M'arrossego" << endl;
    }
};

int main()
{
//SapCaminar<Sapnedar<Customer> > c;
//    Sapnedar c;
Especialitzacio c;
    c.print();
    c.neda();
    return 0;
}


