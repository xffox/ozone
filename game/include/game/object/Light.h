#ifndef GAME_OBJECT_LIGHT_H
#define GAME_OBJECT_LIGHT_H

#include <memory>

#include "geom/Point.h"
#include "ozone/GameObject.h"

namespace render
{
    class LightDrawer;
}

namespace game
{
    namespace object
    {

    class Light: public ozone::GameObject
    {
    public:
        Light()
            :position(), lightDrawer()
        {
        }

        virtual ~Light();

        virtual void draw(render::Drawer *drawer);

        virtual const std::string &getType() const
        {
            return type;
        }

        void setPosition(const geom::Point &position);

        const geom::Point &getPosition() const
        {
            return position;
        }

        void setLightDrawer(std::auto_ptr<render::LightDrawer> lightDrawer);

    private:
        geom::Point position;
        std::auto_ptr<render::LightDrawer> lightDrawer;

    private:
        static const std::string type;
    };

    }
}

#endif
