#include "game/NativeGameLogic.h"

#include <cassert>
#include <math.h>

#include "render/Color.h"
#include "render/Event.h"
#include "render/KeyboardEvent.h"
#include "render/MouseMotionEvent.h"
#include "ozone/GameObjectFactory.h"

#include "game/object/Point.h"
#include "game/object/Wall.h"
#include "game/object/Light.h"

using namespace ozone;

namespace
{
    void move(ViewPos &pos, const ViewPos &displacement,
        const ViewAngle &displacementDirection)
    {
        const double xAngle = displacementDirection[0].getRadian();
        const double yAngle = displacementDirection[1].getRadian();
        pos[0] += displacement[0]*cos(yAngle);
        pos[2] -= displacement[0]*sin(yAngle);
        pos[0] += displacement[2]*sin(yAngle)*cos(xAngle);
        pos[1] -= displacement[2]*sin(xAngle);
        pos[2] += displacement[2]*cos(yAngle)*cos(xAngle);
    }
}

namespace game
{

NativeGameLogic::NativeGameLogic(GameObjectFactory *factory)
    :GameLogic(factory), factory(factory), walls(),
    mouseX(0), mouseY(0)
{
}

void NativeGameLogic::load(WorldModel::WorldAccess *worldAccess)
{
    worldAccess->clear();

    createWall(worldAccess,
        geom::Point(.0, .0, -20.0),
        20.0, 20.0, geom::Angle(M_PI),
        render::Color(1.0, .0, .0));

    createWall(worldAccess,
        geom::Point(.0, .0, 20.0),
        20.0, 20.0, geom::Angle(.0),
        render::Color(.0, 1.0, .0));

    createWall(worldAccess,
        geom::Point(10.0, .0, .0),
        40.0, 20.0, geom::Angle(M_PI_2),
        render::Color(.0, .0, 1.0));

    createWall(worldAccess,
        geom::Point(-10.0, .0, .0),
        40.0, 20.0, geom::Angle(-M_PI_2),
        render::Color(1.0, 1.0, .0));

    createLight(worldAccess,
        geom::Point(5.0, 5.0, -10.0));
}

void NativeGameLogic::save(WorldModel::WorldAccess*)
{
}

void NativeGameLogic::run(WorldModel::WorldAccess*,
    Time)
{
}

void NativeGameLogic::process(WorldModel::WorldAccess *worldAccess,
    const render::Event &event)
{
    {
        const render::KeyboardEvent *keyboardEvent =
            dynamic_cast<const render::KeyboardEvent*>(&event);
        if(keyboardEvent)
        {
            ViewPos viewPos = worldAccess->getViewPos();
            const ViewAngle &viewAngle = worldAccess->getViewAngle();
            ViewPos displacement(3);
            bool moved = false;
            switch(keyboardEvent->getKey())
            {
            case 's':
                displacement[0] = .0f;
                displacement[2] = 1.0f;
                move(viewPos, displacement, viewAngle);
                moved = true;
                break;
            case 'w':
                displacement[0] = .0f;
                displacement[2] = -1.0f;
                move(viewPos, displacement, viewAngle);
                moved = true;
                break;
            case 'd':
                displacement[0] = 1.0f;
                displacement[2] = .0f;
                move(viewPos, displacement, viewAngle);
                moved = true;
                break;
            case 'a':
                displacement[0] = -1.0f;
                displacement[2] = .0f;
                move(viewPos, displacement, viewAngle);
                moved = true;
                break;
            }
            if(moved)
                worldAccess->setViewPos(viewPos);
            return;
        }
    }
    {
        const render::MouseMotionEvent *mouseMotionEvent =
            dynamic_cast<const render::MouseMotionEvent*>(&event);
        if(mouseMotionEvent)
        {
            ViewAngle viewAngle = worldAccess->getViewAngle();
            viewAngle[1].setDegrees(viewAngle[1].getDegrees() +
                mouseX - mouseMotionEvent->getX());
            double xAngle = viewAngle[0].getDegrees() +
                mouseY - mouseMotionEvent->getY();
            if(xAngle < -90.0)
                xAngle = -90.0;
            else if(xAngle > 90.0)
                xAngle = 90.0;
            viewAngle[0].setDegrees(xAngle);
            mouseY = mouseMotionEvent->getY();
            mouseX = mouseMotionEvent->getX();
            worldAccess->setViewAngle(viewAngle);
            return;
        }
    }
}

void NativeGameLogic::createWall(ozone::WorldModel::WorldAccess *worldAccess,
    const geom::Point &center, float width, float height,
    const geom::Angle &yAngle, const render::Color &color)
{
    object::Wall *wall = dynamic_cast<object::Wall*>(
        factory->CreateObject(worldAccess, "wall"));
    assert(wall);

    wall->setCenter(center);
    wall->setWidth(width);
    wall->setHeight(height);
    wall->setYAngle(yAngle);
    wall->setColor(color);

    walls.push_back(wall);
}

void NativeGameLogic::createLight(ozone::WorldModel::WorldAccess *worldAccess,
            const geom::Point &position)
{
    object::Light *light = dynamic_cast<object::Light*>(
        factory->CreateObject(worldAccess, "light"));
    assert(light);

    light->setPosition(position);
}

}
