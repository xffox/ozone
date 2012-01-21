#ifndef UTIL_OBSERVABLE_H
#define UTIL_OBSERVABLE_H

#include <list>
#include <algorithm>
#include <exception>

namespace util
{
    //! Notifications mechanism.
    /*!
     * Implements observer pattern.
     */
    template<class Observer>
    class Observable
    {
        typedef std::list<Observer*> ObserversContainer;
    public:
        Observable()
            :observers()
        {
        }

        virtual ~Observable() = 0;

        //! Add observer.
        /*!
         * Duplicates are ignored. NULL will raise an exception.
         */
        void addObserver(Observer *observer);
        //! Remove observer.
        /*!
         * Not found observers are ingored. NULL will raise an exception.
         */
        void removeObserver(Observer *observer);

    protected:
        //! Notify observers by calling notifyFunc on them.
        /*!
         * Notification is represented by a functor that had to
         * accept observer pointer parameter.
         */
        template<class Func>
        void notify(Func notifyFunc);

    private:
        ObserversContainer observers;
    };

    template<class Observer>
    Observable<Observer>::~Observable()
    {
    }

    template<class Observer>
    void Observable<Observer>::addObserver(Observer *observer)
    {
        if(!observer)
            throw std::exception();
        if(std::find(observers.begin(), observers.end(), observer) ==
            observers.end())
        {
            observers.push_back(observer);
        }
    }

    template<class Observer>
    void Observable<Observer>::removeObserver(Observer *observer)
    {
        if(!observer)
            throw std::exception();
        observers.remove(observer);
    }

    template<class Observer>
    template<class Func>
    void Observable<Observer>::notify(Func notifyFunc)
    {
        // TODO: remove during notification support
        std::for_each(observers.begin(), observers.end(), notifyFunc);
    }
}

#endif
