#include "game/object/Point.h"

#include "render/Drawer.h"
#include "render/Color.h"

namespace game
{
namespace object
{

Point::Point()
    :x(.0f), y(.0f)
{
}

Point::Point(float x, float y)
    :x(x), y(y)
{
}

void Point::draw(render::Drawer *drawer)
{
    drawer->drawPoint(x, y, render::Color(.0f, 1.0f, .0f));
}

const std::string Point::type("point");

}
}
