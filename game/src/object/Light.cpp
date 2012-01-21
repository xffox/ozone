#include "game/object/Light.h"

#include "render/Color.h"
#include "render/Drawer.h"
#include "render/LightDrawer.h"
#include "render/View.h"

namespace game
{
namespace object
{

Light::~Light()
{
}

void Light::draw(render::Drawer*)
{
}

void Light::setPosition(const geom::Point &position)
{
    this->position = position;
    if(lightDrawer.get())
        lightDrawer->setPosition(position);
}

void Light::setLightDrawer(std::auto_ptr<render::LightDrawer> lightDrawer)
{
    this->lightDrawer = lightDrawer;
    if(this->lightDrawer.get())
    {
        this->lightDrawer->setPosition(position);
        this->lightDrawer->enable();
    }
}

const std::string Light::type("light");

}
}
