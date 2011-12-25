#ifndef OZONE_WORLD_H
#define OZONE_WORLD_H

#include <vector>

#include "Defs.h"

namespace ozone
{
    class GameObject;

    class World
    {
    public:
        typedef std::vector<GameObject*> GameObjects;

    public:
        World();
        ~World();

        void add(GameObject *object);
        void remove(GameObject *object);
        void clear();

        const ViewPos &getViewPos() const
        {
            return viewPos;
        }

        void setViewPos(const ViewPos &viewPos)
        {
            this->viewPos = viewPos;
        }

    private:
        World(const World &);
        World &operator=(const World &);

        void clearObjects();

    public:
        // TODO: private
        GameObjects gameObjects;
        ViewPos viewPos;
    };
}

#endif
