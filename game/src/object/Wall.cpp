#include "game/object/Wall.h"

#include <vector>

#include "render/Drawer.h"

namespace game
{
namespace object
{
Wall::Wall()
    :center(), width(.0f), height(.0f), yAngle(), color(.0, .0, .0),
    verticesData()
{
    verticesData.resize(4);
}

Wall::Wall(const geom::Point &center, float width, float height,
    const geom::Angle &yAngle, const render::Color &color)
    :center(center), width(width), height(height), yAngle(yAngle),
    color(color), verticesData()
{
    verticesData.resize(4);
    updateVertices();
}

void Wall::setColor(const render::Color &color)
{
    this->color = color;
    updateVertices();
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

    drawer->drawQuadrilateralsStrip(verticesData);

    drawer->popModelView();
}

void Wall::updateVertices()
{
    verticesData.getVertex<float>(BOTTOM_LEFT).at(0) = -width/2.0;
    verticesData.getVertex<float>(BOTTOM_LEFT).at(1) = -height/2.0;
    verticesData.getVertex<float>(TOP_LEFT).at(0) = -width/2.0;
    verticesData.getVertex<float>(TOP_LEFT).at(1) = height/2.0;
    verticesData.getVertex<float>(BOTTOM_RIGHT).at(0) = width/2.0;
    verticesData.getVertex<float>(BOTTOM_RIGHT).at(1) = -height/2.0;
    verticesData.getVertex<float>(TOP_RIGHT).at(0) = width/2.0;
    verticesData.getVertex<float>(TOP_RIGHT).at(1) = height/2.0;

    typedef std::vector<float> NormalContainer;
    NormalContainer normalBuf(3);
    normalBuf[0] = .0f;
    normalBuf[1] = .0f;
    normalBuf[2] = -1.0f;
    verticesData.getNormal<float>(BOTTOM_LEFT) = normalBuf;
    verticesData.getNormal<float>(TOP_LEFT) = normalBuf;
    verticesData.getNormal<float>(BOTTOM_RIGHT) = normalBuf;
    verticesData.getNormal<float>(TOP_RIGHT) = normalBuf;

    typedef std::vector<float> ColorContainer;
    ColorContainer colorBuf(3);
    colorBuf[0] = color.r;
    colorBuf[1] = color.g;
    colorBuf[2] = color.b;
    verticesData.getColor<float>(BOTTOM_LEFT) = colorBuf;
    verticesData.getColor<float>(TOP_LEFT) = colorBuf;
    verticesData.getColor<float>(BOTTOM_RIGHT) = colorBuf;
    verticesData.getColor<float>(TOP_RIGHT) = colorBuf;
}

const std::string Wall::type("wall");

}
}
