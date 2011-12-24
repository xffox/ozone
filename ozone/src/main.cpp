#include "render/opengl/OpenglRender.h"

#include <memory>

#include "ozone/RenderClient.h"
#include "ozone/EventClient.h"
#include "ozone/World.h"
#include "ozone/WorldModel.h"
#include "ozone/GameLogic.h"
#include "ozone/NativeGameLogic.h"
#include "ozone/NativeGameObjectFactory.h"
#include "ozone/GameLogicExecutor.h"
#include "ozone/RenderLogic.h"
#include "ozone/NativeRenderLogic.h"

using namespace render::opengl;
using namespace ozone;

int main()
{

    std::auto_ptr<World> world(new World);
    std::auto_ptr<WorldModel> worldModel(new WorldModel(world.get()));

    std::auto_ptr<RenderLogic> renderLogic(new NativeRenderLogic);

    std::auto_ptr<RenderClient> renderClient(new RenderClient(
                worldModel.get(), renderLogic.get()));

    std::auto_ptr<GameObjectFactory> factory(new NativeGameObjectFactory);
    std::auto_ptr<GameLogic> gameLogic(new NativeGameLogic(factory.get()));

    GameLogicExecutor executor(gameLogic.get(), worldModel.get());
    std::auto_ptr<EventClient> eventClient(new EventClient(&executor));

    OpenglRender render;
    render.init(renderClient.get(), eventClient.get());

    executor.exec();

    render.destroy();

    return 0;
}
