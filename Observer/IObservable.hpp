#pragma once
#include "IObserver.hpp"
#include <vector>
//#define POINTER_OBSERVABLE
#ifndef POINTER_OBSERVABLE

class IObservable
{
public:
   void registerObserver(IObserver& observer)
   {
      this->observersList.push_back(observer);
   }

   void notifyObservers() const
   {
      for(IObserver& ob : this->observersList)
      {
         ob.onNotify();
      }
   }

   bool removeObserver(const IObserver& observer)
   {
      if(const auto it = std::find_if(this->observersList.begin(), this->observersList.end(), [&observer](const IObserver& ob)
         {
            return &observer == &ob;
         }); 
         this->observersList.end() != it)
      {
         this->observersList.erase(it);
         return true;
      }
      else
      {
         return false;
      }
   }
private:
   std::vector<std::reference_wrapper<IObserver>> observersList;
};


#else

class IObservable
{
public:
   void registerObserver(IObserver* observer)
   {
      this->observersList.push_back(observer);
   }

   void notifyObservers() const
   {
      for(auto& ob : this->observersList)
      {
         ob->onNotify();
      }
   }

   bool removeObserver(const IObserver* observer)
   {
      if(const auto it = std::find_if(this->observersList.begin(), this->observersList.end(), [&observer](const IObserver* ob)
         {
            return observer == ob;
         });
      this->observersList.end() != it)
      {
         this->observersList.erase(it);
         return true;
      }
      else
      {
         return false;
      }
   }
private:
   std::vector<IObserver*> observersList;
};
#endif