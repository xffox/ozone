#include "render/opengl/glsl/ShaderObject.h"

#include "render/opengl/glsl/ShaderCompileException.h"

namespace render
{
namespace opengl
{
namespace glsl
{

void ShaderObject::loadSource(const std::string &source)
{
    const GLuint name = getName();
    const char *strings[] = {source.c_str()};
    glShaderSource(name, sizeof(strings)/sizeof(strings[0]), strings, NULL);
}

void ShaderObject::compile()
{
    const GLuint name = getName();
    glCompileShader(name);
    GLint res = 0;
    glGetShaderiv(name, GL_COMPILE_STATUS, &res);
    if(res != GL_TRUE)
    {
        GLint logLength = 0;
        glGetShaderiv(name, GL_INFO_LOG_LENGTH, &logLength);
        std::string log;
        if(logLength > 0)
        {
            log.resize(logLength);
            glGetShaderInfoLog(name, logLength, NULL, &log[0]);
        }
        throw ShaderCompileException(log);
    }
}

}
}
}
