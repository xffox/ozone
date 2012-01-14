#ifndef RENDER_OPENGL_GLSL_SHADER_COMPILER_H
#define RENDER_OPENGL_GLSL_SHADER_COMPILER_H

#include <string>
#include <memory>
#include <vector>

namespace render
{
    namespace opengl
    {
    namespace glsl
    {

    class ShaderObject;
    class ProgramObject;

    class ShaderCompiler
    {
    public:
        typedef std::vector<ShaderObject*> ShaderObjectsContainer;

    public:
        std::auto_ptr<ShaderObject> compileVertexShader(
            const std::string &source) const;
        std::auto_ptr<ShaderObject> compileFragmentShader(
            const std::string &source) const;

        std::auto_ptr<ProgramObject> link(
            const ShaderObjectsContainer &shaderObjects) const;

    private:
        std::auto_ptr<ShaderObject> compile(
            std::auto_ptr<ShaderObject> shaderObject,
            const std::string &source) const;
    };

    }
    }
}

#endif
