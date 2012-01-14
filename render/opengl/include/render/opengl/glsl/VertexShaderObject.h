#ifndef RENDER_OPENGL_GLSL_VERTEX_SHADER_OBJECT_H
#define RENDER_OPENGL_GLSL_VERTEX_SHADER_OBJECT_H

#include <GL/glew.h>
#include <GL/gl.h>

#include "render/opengl/glsl/ShaderObject.h"

namespace render
{
    namespace opengl
    {
    namespace glsl
    {

    class VertexShaderObject: public ShaderObject
    {
        friend class ShaderCompiler;

    public:
        virtual ~VertexShaderObject();

    protected:
        VertexShaderObject();

        virtual GLuint getName() const
        {
            return name;
        }

    private:
        VertexShaderObject(const VertexShaderObject&);
        VertexShaderObject &operator=(const VertexShaderObject&);

    private:
        GLuint name;
    };

    }
    }
}

#endif
