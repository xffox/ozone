#include "render/opengl/OpenglLightDrawer.h"

#include <exception>
#include <cassert>

#include "geom/Point.h"

namespace render
{
namespace opengl
{

OpenglLightDrawer::OpenglLightDrawer()
    :light()
{
    size_t lightIndex = 0;
    if(!lightIndexProvider.acquire(lightIndex))
        throw std::exception();
    light = GL_LIGHT0 + lightIndex;

    try
    {
        glGetError();
        GLfloat ambient[] = {0.3f, 0.3f, 0.3f, 0.3f};
        glLightfv(light, GL_AMBIENT, ambient);
        if(glGetError() != GL_NO_ERROR)
            throw std::exception();
        GLfloat diffuse[] = {0.7f, 0.7f, 0.7f, 1.0f};
        glLightfv(light, GL_DIFFUSE, diffuse);
        if(glGetError() != GL_NO_ERROR)
            throw std::exception();
    }
    catch(...)
    {
        lightIndexProvider.release(lightIndex);
        throw;
    }
}

OpenglLightDrawer::~OpenglLightDrawer()
{
    try
    {
        disable();
    }
    catch(...)
    {
        // TODO: log
    }

    assert(light >= GL_LIGHT0);
    try
    {
        lightIndexProvider.release(light - GL_LIGHT0);
    }
    catch(...)
    {
        // TODO: log
    }
}

void OpenglLightDrawer::enable()
{
    glGetError();
    glEnable(light);
    if(glGetError() != GL_NO_ERROR)
        throw std::exception();
}

void OpenglLightDrawer::disable()
{
    glGetError();
    glDisable(light);
    if(glGetError() != GL_NO_ERROR)
        throw std::exception();
}

void OpenglLightDrawer::setPosition(const geom::Point &position)
{
    GLfloat lightPosition[] = {position.x, position.y, position.z, 1.0f};
    glLightfv(light, GL_POSITION, lightPosition);
}

util::IndexProvider OpenglLightDrawer::lightIndexProvider(8);
}
}
