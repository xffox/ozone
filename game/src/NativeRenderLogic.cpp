#include "game/NativeRenderLogic.h"

#include <sstream>
#include <math.h>

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

    const ViewAngle &viewAngle = worldAccess->getViewAngle();
    drawer->rotate(viewAngle[2].getDegrees(), .0f, .0f, 1.0f);
    drawer->rotate(viewAngle[0].getDegrees(), 1.0f, .0f, .0f);
    drawer->rotate(viewAngle[1].getDegrees(), .0f, 1.0f, .0f);

    const ViewPos &viewPos = worldAccess->getViewPos();
    drawer->move(viewPos[0], viewPos[1], viewPos[2]);

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
