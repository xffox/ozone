#include "game/NativeGameObjectFactory.h"

#include <memory>

#include "game/object/Point.h"
#include "game/object/Wall.h"
#include "game/object/Light.h"

using namespace ozone;

namespace game
{

GameObject *NativeGameObjectFactory::CreateObject(
    WorldModel::WorldAccess *access, const std::string &type)
{
    std::auto_ptr<GameObject> gameObject;
    if("point" == type)
    {
        gameObject.reset(new object::Point);
    }
    if("wall" == type)
    {
        gameObject.reset(new object::Wall);
    }
    if("light" == type)
    {
        gameObject.reset(new object::Light);
    }

    if(gameObject.get())
        access->add(gameObject.get());

    return gameObject.release();
}

}
