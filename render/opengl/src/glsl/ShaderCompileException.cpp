#include "render/opengl/glsl/ShaderCompileException.h"

namespace render
{
namespace opengl
{
namespace glsl
{

const char *ShaderCompileException::what() const throw()
{
    return "shader compile exception";
}

}
}
}
