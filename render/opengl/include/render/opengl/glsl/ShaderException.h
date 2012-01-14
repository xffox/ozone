#ifndef RENDER_OPENGL_GLSL_SHADER_EXCEPTION_H
#define RENDER_OPENGL_GLSL_SHADER_EXCEPTION_H

#include <exception>
#include <string>

namespace render
{
    namespace opengl
    {
    namespace glsl
    {

    class ShaderException: public std::exception
    {
    public:
        virtual ~ShaderException() throw(){}
        virtual const char *what() const throw();
    };

    }
    }
}

#endif
