#include "IObserver.hpp"
#include "IObservable.hpp"
#include <iostream>

//Testing class
class ConcreteObserver : public IObserver
{
public:
   ConcreteObserver(const std::string& name)
   {
      this->name = name;
   }

   void onNotify() override
   {
      std::cout << "Notified in " << this->name << std::endl;
   }

   bool operator==(const ConcreteObserver& other)
   {
      return this->name == other.name;
   }

private:
   std::string name;
};


//Testing class
class ConcreteObservable : public IObservable
{
public:
   void doSomething()
   {
      notifyObservers();
   }
};

int main()
{
   ConcreteObserver c1{ "1" };
   ConcreteObserver c2{ "2" };
   ConcreteObserver c3{ "3" };
   ConcreteObservable observable;

#ifndef POINTER_OBSERVABLE

   observable.registerObserver(c1);
   observable.registerObserver(c2);
   observable.registerObserver(c3);

   observable.doSomething();

   observable.removeObserver(c1);

   observable.doSomething();
#else
   observable.registerObserver(&c1);
   observable.registerObserver(&c2);
   observable.registerObserver(&c3);

   observable.doSomething();

   observable.removeObserver(&c1);

   observable.doSomething();
#endif
}