#include "render/opengl/View.h"

#include <GL/glu.h>

#include <exception>
#include <cassert>

#include "render/Client.h"

namespace render
{
namespace opengl
{
View::View()
    :client(NULL), drawer()
{
}

View::~View()
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

void View::init(Client *client)
{
    if(!client)
        throw std::exception();
    if(this->client)
        throw std::exception();

    this->client = client;

    prepare();
}

void View::destroy()
{
    if(!client)
        throw std::exception();

    client = NULL;
}

bool View::isInited() const
{
    return client != NULL;
}

void View::draw()
{
    assert(client);

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
    client->draw(&drawer);
    glFlush();
}

void View::prepare()
{
    glEnable(GL_DEPTH_TEST);
    glClearColor(.0, .0, .0, .0);
    glMatrixMode(GL_PROJECTION);
    gluPerspective(90.0, 4.0/3.0, 0.1f, 200.0f);
}
}
}
