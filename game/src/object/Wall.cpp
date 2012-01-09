#include "game/object/Wall.h"

#include "render/Drawer.h"

namespace game
{
namespace object
{
Wall::Wall()
    :vertices(), color(.0f, .0f, .0f)
{
    vertices.resize(4, geom::Point(.0, .0, .0));
}

Wall::Wall(const geom::Point &bottomLeft, const geom::Point &topLeft,
    const geom::Point &bottomRight, const geom::Point &topRight,
    const render::Color &color)
    :vertices(), color(color)
{
    vertices.reserve(4);
    vertices.push_back(bottomLeft);
    vertices.push_back(topLeft);
    vertices.push_back(bottomRight);
    vertices.push_back(topRight);
}

void Wall::setBottomLeft(const geom::Point &p)
{
    vertices[BOTTOM_LEFT] = p;
}

void Wall::setTopLeft(const geom::Point &p)
{
    vertices[TOP_LEFT] = p;
}

void Wall::setBottomRight(const geom::Point &p)
{
    vertices[BOTTOM_RIGHT] = p;
}

void Wall::setTopRight(const geom::Point &p)
{
    vertices[TOP_RIGHT] = p;
}

const geom::Point &Wall::getBottomLeft() const
{
    return vertices[BOTTOM_LEFT];
}

const geom::Point &Wall::getTopLeft() const
{
    return vertices[TOP_LEFT];
}

const geom::Point &Wall::getBottomRight() const
{
    return vertices[BOTTOM_RIGHT];
}

const geom::Point &Wall::getTopRight() const
{
    return vertices[TOP_RIGHT];
}

void Wall::setColor(const render::Color &color)
{
    this->color = color;
}

void Wall::draw(render::Drawer *drawer)
{
    drawer->drawQuadrilateralsStrip(vertices, color);
}

}
}
