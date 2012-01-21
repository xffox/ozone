#ifndef OZONE_WORLD_OBSERVER_H
#define OZONE_WORLD_OBSERVER_H

namespace ozone
{
    class GameObject;

    class WorldObserver
    {
    public:
        virtual ~WorldObserver(){}

        virtual void added(GameObject *object) = 0;
        virtual void removed(GameObject *object) = 0;
        virtual void cleared() = 0;
    };
}

#endif
