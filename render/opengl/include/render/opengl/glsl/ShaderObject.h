#ifndef RENDER_OPENGL_GLSL_SHADER_OBJECT_H
#define RENDER_OPENGL_GLSL_SHADER_OBJECT_H

#include <GL/glew.h>
#include <GL/gl.h>
#include <string>

namespace render
{
    namespace opengl
    {
    namespace glsl
    {

    class ShaderObject
    {
        friend class ShaderCompiler;

    public:
        virtual ~ShaderObject(){}

    protected:
        ShaderObject(){}

        virtual GLuint getName() const = 0;

        virtual void loadSource(const std::string &source);
        virtual void compile();
    };

    }
    }
}

#endif
