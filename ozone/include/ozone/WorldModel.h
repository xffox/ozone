#ifndef OZONE_WORLD_MODEL_H
#define OZONE_WORLD_MODEL_H

#include "util/Mutex.h"

#include <memory>
#include <cstddef>

#include "util/Observable.h"

#include "Defs.h"

namespace ozone
{
    class World;
    class GameObject;
    class WorldObserver;

    class WorldModel: public util::Observable<WorldObserver>
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

            const ViewAngle &getViewAngle() const;
            void setViewAngle(const ViewAngle &viewAngle);

            void addObserver(WorldObserver *observer);
            void removeObserver(WorldObserver *observer);

        private:
            WorldAccess(const WorldAccess&);
            WorldAccess &operator=(const WorldAccess&);

        private:
            WorldModel *worldModel;

        };

    public:
        WorldModel(World *world);

        std::auto_ptr<WorldAccess> access();

    private:
        WorldModel(const WorldModel&);
        WorldModel &operator=(const WorldModel&);

        void notifyAdded(GameObject *object);
        void notifyRemoved(GameObject *object);
        void notifyCleared();

    private:
        World *world;

        util::Mutex accessMutex;
    };
}

#endif
