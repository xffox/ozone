#ifndef RENDER_OPENGL_GLSL_SHADER_COMPILE_EXCEPTION_H
#define RENDER_OPENGL_GLSL_SHADER_COMPILE_EXCEPTION_H

#include <string>

#include "render/opengl/glsl/ShaderException.h"

namespace render
{
    namespace opengl
    {
    namespace glsl
    {

    class ShaderCompileException: public ShaderException
    {
    public:
        ShaderCompileException(const std::string &log)
            :log(log)
        {
        }

        virtual ~ShaderCompileException() throw(){}

        virtual const char *what() const throw();

        const std::string &getLog() const
        {
            return log;
        }

    private:
        const std::string log;
    };

    }
    }
}

#endif
