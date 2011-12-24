#include "util/Condition.h"

#include <cassert>

#include "util/ConditionPrivate.h"

namespace util
{
Condition::Condition()
    :conditionPrivate(new ConditionPrivate)
{
}

Condition::~Condition()
{
    delete conditionPrivate;
}

void Condition::wait(Mutex &mutex)
{
    assert(conditionPrivate);
    conditionPrivate->wait(mutex);
}

bool Condition::timedWait(Mutex &mutex, const Time &timeout)
{
    assert(conditionPrivate);
    return conditionPrivate->timedWait(mutex, timeout);
}

void Condition::notifyOne()
{
    assert(conditionPrivate);
    conditionPrivate->notifyOne();
}

void Condition::notifyAll()
{
    assert(conditionPrivate);
    conditionPrivate->notifyAll();
}

}
