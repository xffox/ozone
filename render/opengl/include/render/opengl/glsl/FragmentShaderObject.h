#ifndef RENDER_OPENGL_GLSL_FRAGMENT_SHADER_OBJECT_H
#define RENDER_OPENGL_GLSL_FRAGMENT_SHADER_OBJECT_H

#include "render/opengl/glsl/ShaderObject.h"

namespace render
{
    namespace opengl
    {
    namespace glsl
    {

    class FragmentShaderObject: public ShaderObject
    {
        friend class ShaderCompiler;

    public:
        virtual ~FragmentShaderObject();

    protected:
        FragmentShaderObject();

        virtual GLuint getName() const
        {
            return name;
        }

    private:
        FragmentShaderObject(const FragmentShaderObject&);
        FragmentShaderObject &operator=(const FragmentShaderObject&);

    private:
        GLuint name;
    };

    }
    }
}

#endif
