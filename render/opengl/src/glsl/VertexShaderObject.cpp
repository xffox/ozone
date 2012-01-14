#include "render/opengl/glsl/VertexShaderObject.h"

#include <exception>

namespace render
{
namespace opengl
{
namespace glsl
{

VertexShaderObject::VertexShaderObject()
    :name(glCreateShader(GL_VERTEX_SHADER))
{
    if(0 == name)
        throw std::exception();
}

VertexShaderObject::~VertexShaderObject()
{
    glDeleteShader(name);
}

}
}
}
