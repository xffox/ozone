#include "game/NativeRenderLogic.h"

#include <sstream>
#include <math.h>
#include <cassert>
#include <fstream>
#include <iterator>
#include <algorithm>
#include <iostream>

#include "render/Drawer.h"
#include "render/View.h"
#include "ozone/GameObject.h"

#include "render/opengl/glsl/ShaderCompiler.h"
#include "render/opengl/glsl/ShaderObject.h"
#include "render/opengl/glsl/ProgramObject.h"
#include "render/opengl/glsl/ShaderException.h"
#include "render/opengl/glsl/ShaderCompileException.h"
#include "render/opengl/glsl/ShaderLinkException.h"

#include "game/object/Light.h"

using namespace ozone;
using namespace render::opengl::glsl;

namespace
{
    bool readFile(std::string &data, const std::string &filename)
    {
        std::fstream file(filename.c_str(),
            std::fstream::in|std::fstream::binary);
        if(file)
        {
            data.clear();
            std::istreambuf_iterator<char> begin(file);
            std::istreambuf_iterator<char> end;
            std::copy(begin, end, std::back_inserter(data));

            file.close();

            return true;
        }
        return false;
    }
}

namespace game
{

NativeRenderLogic::NativeRenderLogic()
    :fpsCounter(), fps(0), view(NULL), shaderProgram(), lights()
{
}

void NativeRenderLogic::init(render::View *view,
    WorldModel::WorldAccess *worldAccess)
{
    if(!view)
        throw std::exception();
    if(!worldAccess)
        throw std::exception();

    this->view = view;

    try
    {
        initShaders();
    }
    catch(ShaderCompileException &exc)
    {
        std::cerr<<"shader compile error: "<<exc.getLog()<<std::endl;
    }
    catch(ShaderLinkException &exc)
    {
        std::cerr<<"shader link error: "<<exc.getLog()<<std::endl;
    }
    catch(ShaderException &exc)
    {
        std::cerr<<"shader error: "<<std::endl;
    }

    worldAccess->addObserver(this);

    initLights(worldAccess);
}

void NativeRenderLogic::destroy(WorldModel::WorldAccess *worldAccess)
{
    worldAccess->removeObserver(this);
    clearLights();

    view = NULL;
}

void NativeRenderLogic::draw(WorldModel::WorldAccess *worldAccess,
    render::Drawer *drawer)
{
    if(!worldAccess || !drawer)
        return;

    if(shaderProgram.get())
        shaderProgram->use();

    const ViewAngle &viewAngle = worldAccess->getViewAngle();
    drawer->rotateProjection(-viewAngle[2].getDegrees(), .0f, .0f, 1.0f);
    drawer->rotateProjection(-viewAngle[0].getDegrees(), 1.0f, .0f, .0f);
    drawer->rotateProjection(-viewAngle[1].getDegrees(), .0f, 1.0f, .0f);

    const ViewPos &viewPos = worldAccess->getViewPos();
    drawer->translateProjection(-viewPos[0], -viewPos[1], -viewPos[2]);

    const size_t objectsCount = worldAccess->objectsCount();
    for(size_t i = 0; i < objectsCount; ++i)
        (*worldAccess)[i]->draw(drawer);

    if(shaderProgram.get())
        shaderProgram->reset();

    fps = fpsCounter.frame();

    drawFps(drawer);
}

void NativeRenderLogic::added(GameObject *object)
{
    object::Light *light = dynamic_cast<object::Light*>(object);
    if(light)
        addLight(light);
}

void NativeRenderLogic::removed(GameObject *object)
{
    object::Light *light = dynamic_cast<object::Light*>(object);
    if(light)
        removeLight(light);
}

void NativeRenderLogic::cleared()
{
    clearLights();
}

void NativeRenderLogic::initShaders()
{
    ShaderCompiler compiler;

    std::string shaderSrc;
    if(!readFile(shaderSrc, "shader/brick.vert"))
    {
        return;
    }
    std::auto_ptr<ShaderObject> vertexShaderObject =
        compiler.compileVertexShader(shaderSrc);
    if(!readFile(shaderSrc, "shader/brick.frag"))
    {
        return;
    }
    std::auto_ptr<ShaderObject> fragmentShaderObject =
        compiler.compileFragmentShader(shaderSrc);

    ShaderCompiler::ShaderObjectsContainer shaderObjects;
    shaderObjects.push_back(vertexShaderObject.get());
    shaderObjects.push_back(fragmentShaderObject.get());

    shaderProgram = compiler.link(shaderObjects);
}

void NativeRenderLogic::drawFps(render::Drawer *drawer)
{
    std::stringstream ss;
    ss<<fps<<" fps";
    drawer->drawText(ss.str(), .0f, .0f);
}

void NativeRenderLogic::initLights(ozone::WorldModel::WorldAccess *worldAccess)
{
    assert(worldAccess);
    const size_t objectsCount = worldAccess->objectsCount();
    for(size_t i = 0; i < objectsCount; ++i)
    {
        GameObject *object = (*worldAccess)[i];
        assert(object);
        object::Light* light = dynamic_cast<object::Light*>(object);
        if(light)
            addLight(light);
    }
}

void NativeRenderLogic::addLight(object::Light *light)
{
    assert(light);
    if(std::find(lights.begin(), lights.end(), light) == lights.end())
    {
        lights.push_back(light);
        try
        {
            assert(view);
            std::auto_ptr<render::LightDrawer> lightDrawer(
                view->createLightDrawer());
            light->setLightDrawer(lightDrawer);
        }
        catch(...)
        {
        }
    }
}

void NativeRenderLogic::removeLight(object::Light *light)
{
    assert(light);
    lights.remove(light);
}

void NativeRenderLogic::clearLights()
{
    lights.clear();
}

}
