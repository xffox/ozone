#include "ozone/WorldModel.h"

#include <exception>

#include "ozone/World.h"

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
}

void WorldModel::WorldAccess::remove(GameObject *object)
{
    worldModel->world->remove(object);
}

void WorldModel::WorldAccess::clear()
{
    worldModel->world->clear();
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

}
