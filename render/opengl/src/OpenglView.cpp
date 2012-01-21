#include "render/opengl/OpenglView.h"

#include <GL/glew.h>
#include <GL/glu.h>

#include <exception>
#include <cassert>

#include "render/Client.h"
#include "render/opengl/OpenglDrawer.h"
#include "render/opengl/OpenglLightDrawer.h"

namespace render
{
namespace opengl
{
OpenglView::OpenglView()
    :client(NULL), drawer(new OpenglDrawer(*this))
{
}

OpenglView::~OpenglView()
{
    if(isInited())
    {
        try
        {
            destroy();
        }
        catch(...)
        {
            // TODO: log
        }
    }
}

std::auto_ptr<LightDrawer> OpenglView::createLightDrawer()
{
    return std::auto_ptr<LightDrawer>(new OpenglLightDrawer);
}

void OpenglView::init(Client *client)
{
    if(!client)
        throw std::exception();
    if(this->client)
        throw std::exception();

    this->client = client;

    prepare();
}

void OpenglView::destroy()
{
    if(!client)
        throw std::exception();

    cleanup();

    client = NULL;
}

bool OpenglView::isInited() const
{
    return client != NULL;
}

void OpenglView::draw()
{
    assert(client);

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
    gluPerspective(90.0, 4.0/3.0, 0.1f, 200.0f);
    client->draw(drawer.get());
    glFinish();
//    glFlush();
}

void OpenglView::prepare()
{
    assert(client);

    glewInit();
    glGetError();
    glEnable(GL_DEPTH_TEST);
    if(glGetError() != GL_NO_ERROR)
        throw std::exception();
//    glClearDepth(1.0);
//    glEnable(GL_CULL_FACE);
    glClearColor(.0, .0, .0, 1.0);

    client->init(this);
}

void OpenglView::cleanup()
{
    assert(client);

    client->destroy();
}

}
}
