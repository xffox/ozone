#ifndef UTIL_CONDITION_H
#define UTIL_CONDITION_H

namespace util
{
    class ConditionPrivate;
    class Mutex;
    class Time;

    class Condition
    {
    public:
        Condition();
        ~Condition();

        void wait(Mutex &mutex);
        bool timedWait(Mutex &mutex, const Time &timeout);
        void notifyOne();
        void notifyAll();

    private:
        Condition(const Condition&);
        Condition &operator=(const Condition&);

    private:
        ConditionPrivate *conditionPrivate;
    };
}

#endif
