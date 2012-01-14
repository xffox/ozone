#ifndef RENDER_OPENGL_GLSL_PROGRAM_OBJECT_H
#define RENDER_OPENGL_GLSL_PROGRAM_OBJECT_H

#include <GL/glew.h>
#include <GL/gl.h>

namespace render
{
    namespace opengl
    {
    namespace glsl
    {
    class ProgramObject
    {
        friend class ShaderCompiler;

    public:
        virtual ~ProgramObject();

        virtual void use();
        virtual void reset();

    protected:
        ProgramObject();

        virtual void attachShader(GLuint shaderName);
        virtual void detachShader(GLuint shaderName);

        virtual void link();

    private:
        void useProgram(GLuint programName);

    private:
        GLuint name;
    };

    }
    }
}

#endif
