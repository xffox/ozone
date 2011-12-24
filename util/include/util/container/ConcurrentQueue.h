#ifndef UTIL_CONTAINER_CONCURRENT_QUEUE_H
#define UTIL_CONTAINER_CONCURRENT_QUEUE_H

#include <queue>
#include "util/Mutex.h"
#include "util/MutexLocker.h"
#include "util/MultipleMutexLocker.h"

namespace util
{
    namespace container
    {

    template<class T>
    class ConcurrentQueue
    {
        typedef std::queue<T> InternalContainer;

    public:
        ConcurrentQueue();
        ConcurrentQueue(const T &that);
        ~ConcurrentQueue();

        ConcurrentQueue &operator=(const T &that);

        void push(const T &val);
        bool tryPop(T &val);

    private:
        InternalContainer container;
        Mutex mutex;
    };

    template<class T>
    ConcurrentQueue<T>::ConcurrentQueue()
    {
    }

    template<class T>
    ConcurrentQueue<T>::ConcurrentQueue(const T &that)
    {
        MutexLocker lock(&that.mutex);
        container = that.container;
    }

    template<class T>
    ConcurrentQueue<T>::~ConcurrentQueue()
    {
    }

    template<class T>
    ConcurrentQueue<T> &ConcurrentQueue<T>::operator=(const T &that)
    {
        if(this != &that)
        {
            MultipleMutexLocker lock(&mutex, &that.mutex);
            container = that.container;
        }
        return *this;
    }

    template<class T>
    void ConcurrentQueue<T>::push(const T &val)
    {
        MutexLocker lock(&mutex);
        container.push(val);
    }

    template<class T>
    bool ConcurrentQueue<T>::tryPop(T &val)
    {
        MutexLocker lock(&mutex);
        if(!container.empty())
        {
            val = container.front();
            container.pop();
            return true;
        }
        return false;
    }

    }
}

#endif
