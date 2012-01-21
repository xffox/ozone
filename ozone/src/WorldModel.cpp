#include "ozone/WorldModel.h"

#include <exception>
#include <cassert>

#include "ozone/World.h"
#include "ozone/WorldObserver.h"

namespace
{
    class NotifyAdded
    {
    public:
        NotifyAdded(ozone::GameObject *object)
            :object(object)
        {
            assert(object);
        }

        void operator()(ozone::WorldObserver *observer) const
        {
            assert(observer);
            observer->added(object);
        }

    private:
        ozone::GameObject *object;
    };

    class NotifyRemoved
    {
    public:
        NotifyRemoved(ozone::GameObject *object)
            :object(object)
        {
        }

        void operator()(ozone::WorldObserver *observer) const
        {
            assert(observer);
            observer->removed(object);
        }

    private:
        ozone::GameObject *object;
    };

    struct NotifyCleared
    {
        void operator()(ozone::WorldObserver *observer) const
        {
            assert(observer);
            observer->cleared();
        }
    };
}

namespace ozone
{

WorldModel::WorldAccess::WorldAccess(WorldModel *worldModel)
    :worldModel(worldModel)
{
    if(!worldModel)
        throw std::exception();

    worldModel->accessMutex.lock();
}

WorldModel::WorldAccess::~WorldAccess()
{
    worldModel->accessMutex.unlock();
}

GameObject *WorldModel::WorldAccess::operator[](size_t idx)
{
    World::GameObjects &gameObjects = worldModel->world->gameObjects;
    if(idx < gameObjects.size())
        return gameObjects[idx];
    throw std::exception();
}

const GameObject *WorldModel::WorldAccess::operator[](size_t idx) const
{
    return const_cast<WorldModel::WorldAccess*>(this)->operator[](idx);
}

size_t WorldModel::WorldAccess::objectsCount() const
{
    return worldModel->world->gameObjects.size();
}

void WorldModel::WorldAccess::add(GameObject *object)
{
    worldModel->world->add(object);
    worldModel->notifyAdded(object);
}

void WorldModel::WorldAccess::remove(GameObject *object)
{
    worldModel->world->remove(object);
    worldModel->notifyRemoved(object);
}

void WorldModel::WorldAccess::clear()
{
    worldModel->world->clear();
    worldModel->notifyCleared();
}

const ViewPos &WorldModel::WorldAccess::getViewPos() const
{
    return worldModel->world->getViewPos();
}

void WorldModel::WorldAccess::setViewPos(const ViewPos &viewPos)
{
    worldModel->world->setViewPos(viewPos);
}

const ViewAngle &WorldModel::WorldAccess::getViewAngle() const
{
    return worldModel->world->getViewAngle();
}

void WorldModel::WorldAccess::setViewAngle(const ViewAngle &viewAngle)
{
    worldModel->world->setViewAngle(viewAngle);
}

void WorldModel::WorldAccess::addObserver(WorldObserver *observer)
{
    worldModel->addObserver(observer);
}

void WorldModel::WorldAccess::removeObserver(WorldObserver *observer)
{
    worldModel->removeObserver(observer);
}

WorldModel::WorldModel(World *world)
    :world(world), accessMutex()
{
    if(!world)
        throw std::exception();
}

std::auto_ptr<WorldModel::WorldAccess> WorldModel::access()
{
    return std::auto_ptr<WorldAccess>(new WorldAccess(this));
}

// TODO: probably add access object to notifications too
void WorldModel::notifyAdded(GameObject *object)
{
    notify(NotifyAdded(object));
}

void WorldModel::notifyRemoved(GameObject *object)
{
    notify(NotifyRemoved(object));
}

void WorldModel::notifyCleared()
{
    notify(NotifyCleared());
}

}
