#ifndef OZONE_WORLD_H
#define OZONE_WORLD_H

#include <vector>

#include "Defs.h"

namespace ozone
{
    class GameObject;

    //! World state.
    /*!
     * Stores all game object, view state and provides access to them.
     */
    class World
    {
    public:
        typedef std::vector<GameObject*> GameObjects;

    public:
        World();
        ~World();

        //! Add game object to the world.
        /*!
         * Takes responsibility for the object deletion.
         * \param object added game object.
         */
        void add(GameObject *object);
        //! Remove object from the world.
        /*!
         * \param object removed game object.
         */
        void remove(GameObject *object);
        //! Remove all game objects.
        void clear();

        const ViewPos &getViewPos() const
        {
            return viewPos;
        }

        void setViewPos(const ViewPos &viewPos)
        {
            this->viewPos = viewPos;
        }

        const ViewAngle &getViewAngle() const
        {
            return viewAngle;
        }

        void setViewAngle(const ViewAngle &viewAngle)
        {
            this->viewAngle = viewAngle;
        }

    private:
        World(const World &);
        World &operator=(const World &);

        void clearObjects();

    public:
        // TODO: private
        GameObjects gameObjects;

    private:
        ViewPos viewPos;
        // TODO: formal angles definition
        ViewAngle viewAngle;
    };
}

#endif
