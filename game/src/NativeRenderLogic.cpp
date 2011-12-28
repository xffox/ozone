#include "game/NativeRenderLogic.h"

#include <sstream>

#include "render/Drawer.h"
#include "ozone/GameObject.h"

using namespace ozone;

namespace game
{

NativeRenderLogic::NativeRenderLogic()
    :fpsCounter(), fps(0)
{
}

void NativeRenderLogic::draw(WorldModel::WorldAccess *worldAccess,
    render::Drawer *drawer)
{
    if(!worldAccess || !drawer)
        return;

    const ViewPos &viewPos = worldAccess->getViewPos();
    drawer->moveTo(-viewPos[0], -viewPos[1], -viewPos[2]);

    const size_t objectsCount = worldAccess->objectsCount();
    for(size_t i = 0; i < objectsCount; ++i)
        (*worldAccess)[i]->draw(drawer);

    fps = fpsCounter.frame();

    drawFps(drawer);
}

void NativeRenderLogic::drawFps(render::Drawer *drawer)
{
    std::stringstream ss;
    ss<<fps<<" fps";
    drawer->drawText(ss.str(), .0f, .0f);
}

}
