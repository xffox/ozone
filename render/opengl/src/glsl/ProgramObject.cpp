#include "render/opengl/glsl/ProgramObject.h"

#include <exception>
#include <string>

#include "render/opengl/glsl/ShaderException.h"
#include "render/opengl/glsl/ShaderLinkException.h"

namespace render
{
namespace opengl
{
namespace glsl
{

ProgramObject::ProgramObject()
    :name(glCreateProgram())
{
    if(0 == name)
        throw std::exception();
}

ProgramObject::~ProgramObject()
{
    try
    {
        glDeleteProgram(name);
    }
    catch(...)
    {
    }
}

void ProgramObject::use()
{
    useProgram(name);
}

void ProgramObject::reset()
{
    useProgram(0);
}

void ProgramObject::attachShader(GLuint shaderName)
{
    glAttachShader(name, shaderName);
    if(glGetError() != GL_NO_ERROR)
    {
        throw ShaderException();
    }
}

void ProgramObject::detachShader(GLuint shaderName)
{
    glDetachShader(name, shaderName);
    if(glGetError() != GL_NO_ERROR)
    {
        throw ShaderException();
    }
}

void ProgramObject::link()
{
    glLinkProgram(name);
    GLint res = 0;
    glGetProgramiv(name, GL_LINK_STATUS, &res);
    if(res != GL_TRUE)
    {
        GLint logLength = 0;
        glGetProgramiv(name, GL_INFO_LOG_LENGTH, &logLength);
        std::string log;
        if(logLength > 0)
        {
            log.resize(logLength);
            glGetProgramInfoLog(name, logLength, NULL, &log[0]);
        }
        throw ShaderLinkException(log);
    }
}

void ProgramObject::useProgram(GLuint programName)
{
    glGetError();
    glUseProgram(programName);
    if(glGetError() != GL_NO_ERROR)
    {
        throw ShaderException();
    }
}

}
}
}
