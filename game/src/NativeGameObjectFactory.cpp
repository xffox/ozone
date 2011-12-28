#include "game/NativeGameObjectFactory.h"

#include <memory>

#include "ozone/object/Point.h"
#include "ozone/object/Wall.h"

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

    if(gameObject.get())
        access->add(gameObject.get());

    return gameObject.release();
}

}
