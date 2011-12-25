#include "ozone/World.h"

#include <cstddef>
#include <algorithm>

#include "ozone/GameObject.h"

namespace ozone
{

World::World()
    :gameObjects(), viewPos(3)
{
}

World::~World()
{
    clearObjects();
}

void World::clearObjects()
{
    while(!gameObjects.empty())
    {
        delete gameObjects.back();
        gameObjects.pop_back();
    }
}


void World::add(GameObject *object)
{
    if(object)
        gameObjects.push_back(object);
}

void World::remove(GameObject *object)
{
    for(GameObjects::iterator iter = gameObjects.begin();
            iter != gameObjects.end(); ++iter)
    {
        if(*iter == object)
        {
            delete object;
            gameObjects.erase(iter);
            break;
        }
    }
}

void World::clear()
{
    clearObjects();
}

}
