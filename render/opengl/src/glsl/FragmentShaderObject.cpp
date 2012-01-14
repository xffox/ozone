#include "render/opengl/glsl/FragmentShaderObject.h"

#include <exception>

namespace render
{
namespace opengl
{
namespace glsl
{

FragmentShaderObject::FragmentShaderObject()
    :name(glCreateShader(GL_FRAGMENT_SHADER))
{
    if(0 == name)
        throw std::exception();
}

FragmentShaderObject::~FragmentShaderObject()
{
    glDeleteShader(name);
}

}
}
}
