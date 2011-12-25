#ifndef UTIL_PRODUCER_CONSUMER_H
#define UTIL_PRODUCER_CONSUMER_H

#include <queue>

#include "util/Mutex.h"
#include "util/MutexLocker.h"
#include "util/Condition.h"
#include "util/Time.h"

namespace util
{
    template<class T>
    class ProducerConsumer
    {
        typedef std::queue<T> Container;
    public:
        ProducerConsumer();

        void produce(const T &val);
        bool consume(T &val);
        bool timedConsume(T &val, const Time &timeout);

        void releaseConsumers();

    private:
        template<class Wait>
        bool consume(T &val, Wait wait);

    private:
        Container container;
        Mutex mutex;
        Condition condition;
    };

    class WaitCondition
    {
    public:
        WaitCondition(Condition &condition)
            :condition(&condition)
        {
        }

        bool operator()(Mutex &mutex)
        {
            condition->wait(mutex);
            return true;
        }

    private:
        Condition *condition;
    };

    class TimedWaitCondition
    {
    public:
        TimedWaitCondition(Condition &condition, const Time &timeout)
            :condition(&condition), timeout(timeout)
        {
        }

        bool operator()(Mutex &mutex)
        {
            return condition->timedWait(mutex, timeout);
        }

    private:
        Condition *condition;
        Time timeout;
    };

    template<class T>
    ProducerConsumer<T>::ProducerConsumer()
        :container(), mutex(), condition()
    {
    }

    template<class T>
    void ProducerConsumer<T>::produce(const T &val)
    {
        MutexLocker lock(&mutex);
        container.push(val);
        condition.notifyOne();
    }

    template<class T>
    bool ProducerConsumer<T>::consume(T &val)
    {
        return consume(val, WaitCondition(condition));
    }

    template<class T>
    bool ProducerConsumer<T>::timedConsume(T &val, const Time &timeout)
    {
        return consume(val, TimedWaitCondition(condition, timeout));
    }

    template<class T> template<class Wait>
    bool ProducerConsumer<T>::consume(T &val, Wait wait)
    {
        MutexLocker lock(&mutex);
        // check the container even if the wait timeouted
        if(!container.empty() || (wait(mutex), !container.empty()))
        {
            val = container.front();
            container.pop();
            return true;
        }
        return false;
    }

    template<class T>
    void ProducerConsumer<T>::releaseConsumers()
    {
        condition.notifyAll();
    }
}

#endif
