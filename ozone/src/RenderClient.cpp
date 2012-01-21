#include "ozone/RenderClient.h"

#include "render/Drawer.h"
#include "ozone/WorldModel.h"
#include "ozone/RenderLogic.h"
#include "ozone/GameObject.h"

#include <memory>
#include <exception>
#include <cassert>

namespace ozone
{
RenderClient::RenderClient(WorldModel *model, RenderLogic *renderLogic)
    :model(model), renderLogic(renderLogic)
{
    if(!model || !renderLogic)
        throw std::exception();
}

void RenderClient::init(render::View *view)
{
    assert(renderLogic);
    std::auto_ptr<WorldModel::WorldAccess> access(model->access());
    renderLogic->init(view, access.get());
}

void RenderClient::destroy()
{
    assert(renderLogic);
    std::auto_ptr<WorldModel::WorldAccess> access(model->access());
    renderLogic->destroy(access.get());
}

void RenderClient::draw(render::Drawer *drawer)
{
    assert(renderLogic);

    if(!drawer)
        return;

    std::auto_ptr<WorldModel::WorldAccess> access(model->access());
    renderLogic->draw(access.get(), drawer);
}

}
