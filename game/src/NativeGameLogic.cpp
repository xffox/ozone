#include "game/NativeGameLogic.h"

#include "render/Color.h"
#include "render/KeyboardEvent.h"
#include "ozone/GameObjectFactory.h"
#include "ozone/object/Point.h"
#include "ozone/object/Wall.h"

using namespace ozone;

namespace game
{

NativeGameLogic::NativeGameLogic(GameObjectFactory *factory)
    :GameLogic(factory), factory(factory), walls()
{
}

void NativeGameLogic::load(WorldModel::WorldAccess *worldAccess)
{
    worldAccess->clear();

    createWall(worldAccess,
        geom::Point(-10.0, -10.0, -20.0),
        geom::Point(-10.0, 10.0, -20.0),
        geom::Point(10.0, -10.0, -20.0),
        geom::Point(10.0, 10.0, -20.0),
        render::Color(1.0, .0, .0));

    createWall(worldAccess,
        geom::Point(-10.0, -10.0, 20.0),
        geom::Point(-10.0, 10.0, 20.0),
        geom::Point(-10.0, -10.0, -20.0),
        geom::Point(-10.0, 10.0, -20.0),
        render::Color(.0, .0, 1.0));

    createWall(worldAccess,
        geom::Point(10.0, -10.0, 20.0),
        geom::Point(10.0, 10.0, 20.0),
        geom::Point(10.0, -10.0, -20.0),
        geom::Point(10.0, 10.0, -20.0),
        render::Color(.0, 1.0, .0));
}

void NativeGameLogic::save(WorldModel::WorldAccess*)
{
}

void NativeGameLogic::run(WorldModel::WorldAccess*,
    Time)
{
}

void NativeGameLogic::process(WorldModel::WorldAccess *worldAccess,
    const render::KeyboardEvent &keyboardEvent)
{
    ViewPos viewPos = worldAccess->getViewPos();
    bool moved = false;
    switch(keyboardEvent.getKey())
    {
    case 's':
        viewPos[2] += 1.0f;
        moved = true;
        break;
    case 'w':
        viewPos[2] -= 1.0f;
        moved = true;
        break;
    case 'd':
        viewPos[0] += 1.0f;
        moved = true;
        break;
    case 'a':
        viewPos[0] -= 1.0f;
        moved = true;
        break;
    }
    if(moved)
        worldAccess->setViewPos(viewPos);
}

void NativeGameLogic::createWall(WorldModel::WorldAccess *worldAccess,
    const geom::Point &bottomLeft,
    const geom::Point &topLeft,
    const geom::Point &bottomRight,
    const geom::Point &topRight,
    const render::Color &color)
{
    object::Wall *wall = dynamic_cast<object::Wall*>(
        factory->CreateObject(worldAccess, "wall"));
    wall->setBottomLeft(bottomLeft);
    wall->setTopLeft(topLeft);
    wall->setBottomRight(bottomRight);
    wall->setTopRight(topRight);

    wall->setColor(color);

    walls.push_back(wall);
}

void NativeGameLogic::move(object::Wall &wall, double dist)
{
    geom::Point p;
    p = wall.getBottomLeft();
    p.z -= dist;
    wall.setBottomLeft(p);

    p = wall.getTopLeft();
    p.z -= dist;
    wall.setTopLeft(p);

    p = wall.getBottomRight();
    p.z -= dist;
    wall.setBottomRight(p);

    p = wall.getTopRight();
    p.z -= dist;
    wall.setTopRight(p);
}

}
