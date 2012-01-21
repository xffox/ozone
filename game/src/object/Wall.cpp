#include "game/object/Wall.h"

#include "render/Drawer.h"

namespace game
{
namespace object
{
Wall::Wall()
    :center(), width(.0f), height(.0f), yAngle(), color(.0, .0, .0),
    vertices(4)
{
}

Wall::Wall(const geom::Point &center, float width, float height,
    const geom::Angle &yAngle, const render::Color &color)
    :center(center), width(width), height(height), yAngle(yAngle),
    color(color), vertices(4)
{
    updateVertices();
}

void Wall::setColor(const render::Color &color)
{
    this->color = color;
}

void Wall::setWidth(float width)
{
    this->width = width;
    updateVertices();
}

void Wall::setHeight(float height)
{
    this->height = height;
    updateVertices();
}

void Wall::draw(render::Drawer *drawer)
{
    drawer->pushModelView();
    drawer->translateModelView(center.x, center.y, center.z);
    drawer->rotateModelView(yAngle.getDegrees(), .0f, 1.0f, .0f);
    drawer->drawQuadrilateralsStrip(vertices, color);
    drawer->popModelView();
}

void Wall::updateVertices()
{
    vertices[BOTTOM_LEFT].x = -width/2.0;
    vertices[BOTTOM_LEFT].y = -height/2.0;
    vertices[TOP_LEFT].x = -width/2.0;
    vertices[TOP_LEFT].y = height/2.0;
    vertices[BOTTOM_RIGHT].x = width/2.0;
    vertices[BOTTOM_RIGHT].y = -height/2.0;
    vertices[TOP_RIGHT].x = width/2.0;
    vertices[TOP_RIGHT].y = height/2.0;
}

const std::string Wall::type("wall");

}
}
