#include "render/opengl/glsl/ShaderException.h"

namespace render
{
namespace opengl
{
namespace glsl
{

const char *ShaderException::what() const throw()
{
    return "shader exception";
}

}
}
}
