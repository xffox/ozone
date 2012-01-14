#include "render/opengl/glsl/ShaderCompiler.h"

#include <algorithm>

#include "render/opengl/glsl/VertexShaderObject.h"
#include "render/opengl/glsl/FragmentShaderObject.h"
#include "render/opengl/glsl/ProgramObject.h"
#include "render/opengl/glsl/ShaderException.h"

namespace render
{
namespace opengl
{
namespace glsl
{

std::auto_ptr<ShaderObject> ShaderCompiler::compileVertexShader(
    const std::string &source) const
{
    return compile(std::auto_ptr<ShaderObject>(new VertexShaderObject),
        source);
}

std::auto_ptr<ShaderObject> ShaderCompiler::compileFragmentShader(
    const std::string &source) const
{
    return compile(std::auto_ptr<ShaderObject>(new FragmentShaderObject),
        source);
}

std::auto_ptr<ShaderObject> ShaderCompiler::compile(
    std::auto_ptr<ShaderObject> shaderObject,
    const std::string &source) const
{
    shaderObject->loadSource(source);
    shaderObject->compile();
    return shaderObject;
}

std::auto_ptr<ProgramObject> ShaderCompiler::link(
    const ShaderObjectsContainer &shaderObjects) const
{
    std::auto_ptr<ProgramObject> programObject(new ProgramObject);
    for(ShaderObjectsContainer::const_iterator iter = shaderObjects.begin();
        iter != shaderObjects.end(); ++iter)
    {
        if(*iter)
            programObject->attachShader((*iter)->getName());
    }
    programObject->link();
    return programObject;
}

}
}
}
