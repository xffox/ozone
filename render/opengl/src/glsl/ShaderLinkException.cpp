#include "render/opengl/glsl/ShaderLinkException.h"

namespace render
{
namespace opengl
{
namespace glsl
{

const char *ShaderLinkException::what() const throw()
{
    return "shader link exception";
}

}
}
}
