#ifndef OZONE_WORLD_MODEL_H
#define OZONE_WORLD_MODEL_H

#include "util/Mutex.h"

#include <memory>
#include <cstddef>

#include "Defs.h"

namespace ozone
{
    class World;
    class GameObject;

    class WorldModel
    {
    public:
        class WorldAccess
        {
        public:
            WorldAccess(WorldModel *worldModel);
            ~WorldAccess();

            GameObject *operator[](size_t idx);
            const GameObject *operator[](size_t idx) const;
            size_t objectsCount() const;

            void add(GameObject *object);
            void remove(GameObject *object);
            void clear();

            const ViewPos &getViewPos() const;
            void setViewPos(const ViewPos &viewPos);

        private:
            WorldModel *worldModel;

        };

    public:
        WorldModel(World *world);

        std::auto_ptr<WorldAccess> access();

    private:
        World *world;

        util::Mutex accessMutex;
    };
}

#endif
