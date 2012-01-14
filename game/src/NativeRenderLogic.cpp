#include "game/NativeRenderLogic.h"

#include <sstream>
#include <math.h>
#include <cassert>
#include <fstream>
#include <iterator>
#include <algorithm>

#include "render/Drawer.h"
#include "ozone/GameObject.h"

#include "render/opengl/glsl/ShaderCompiler.h"
#include "render/opengl/glsl/ShaderObject.h"
#include "render/opengl/glsl/ProgramObject.h"
#include "render/opengl/glsl/ShaderException.h"
#include "render/opengl/glsl/ShaderCompileException.h"
#include "render/opengl/glsl/ShaderLinkException.h"

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
    :fpsCounter(), fps(0), shaderProgram()
{
}

void NativeRenderLogic::init()
{
    try
    {
        initShaders();
    }
    catch(ShaderCompileException &exc)
    {
    }
    catch(ShaderLinkException &exc)
    {
    }
    catch(ShaderException &exc)
    {
    }
}

void NativeRenderLogic::destroy()
{
}

void NativeRenderLogic::draw(WorldModel::WorldAccess *worldAccess,
    render::Drawer *drawer)
{
    if(!worldAccess || !drawer)
        return;

    if(shaderProgram.get())
        shaderProgram->use();

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

void NativeRenderLogic::initShaders()
{
    ShaderCompiler compiler;

    std::string shaderSrc;
    if(!readFile(shaderSrc, "shader/temperature.vert"))
    {
        return;
    }
    std::auto_ptr<ShaderObject> vertexShaderObject =
        compiler.compileVertexShader(shaderSrc);
    if(!readFile(shaderSrc, "shader/temperature.frag"))
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

}
