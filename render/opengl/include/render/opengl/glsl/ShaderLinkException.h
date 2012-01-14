#ifndef RENDER_OPENGL_GLSL_SHADER_LINK_EXCEPTION_H
#define RENDER_OPENGL_GLSL_SHADER_LINK_EXCEPTION_H

#include "render/opengl/glsl/ShaderException.h"

namespace render
{
    namespace opengl
    {
    namespace glsl
    {

    class ShaderLinkException: public ShaderException
    {
    public:
        ShaderLinkException(const std::string &log)
            :log(log)
        {
        }

        virtual ~ShaderLinkException() throw(){}

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
