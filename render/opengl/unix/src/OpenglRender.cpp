#include "render/opengl/OpenglRender.h"

#include <GL/glut.h>
#include <cassert>

#include "util/Thread.h"
#include "render/Client.h"
#include "render/EventClient.h"
#include "render/KeyboardEvent.h"

namespace render
{
namespace opengl
{
void OpenglRender::MainLoopRunnable::run()
{
    currentRender->prepare();

    glutDisplayFunc(renderFunc);
    glutIdleFunc(idleFunc);
    glutKeyboardFunc(keyboardFunc);

    currentRender->view.init(currentRender->client);

    glutMainLoop();

    currentRender->view.destroy();
}

OpenglRender::OpenglRender()
    :mainLoopThread(new util::Thread),
    client(NULL), eventClient(NULL)
{
}

OpenglRender::~OpenglRender()
{
#if 0
    destroy();
#endif
}

void OpenglRender::init(Client *client, EventClient *eventClient)
{
    if(!client || !eventClient)
        throw std::exception();
    if(currentRender)
        throw std::exception();

    this->client = client;
    this->eventClient = eventClient;
    currentRender = this;
    mainLoopThread->run(&mainLoopRunnable);
}

void OpenglRender::destroy()
{
    if(!currentRender)
        throw std::exception();

    mainLoopThread->join();
    currentRender = NULL;
    client = NULL;
}

void OpenglRender::prepare()
{
    int argc = 0;
    char *argv[] = {NULL};
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(width, height);
    glutCreateWindow("ozone");
}

KeyboardEvent OpenglRender::buildKeyboardEvent(unsigned char key,
    int modifiers, int, int)
{
    unsigned char buildModifiers = 0;
    if(modifiers & GLUT_ACTIVE_SHIFT)
        buildModifiers |= KeyboardEvent::SHIFT;
    if(modifiers & GLUT_ACTIVE_CTRL)
        buildModifiers |= KeyboardEvent::CTRL;
    if(modifiers & GLUT_ACTIVE_ALT)
        buildModifiers |= KeyboardEvent::ALT;
    return KeyboardEvent(key, modifiers);
}

void OpenglRender::renderFunc()
{
    currentRender->view.draw();
}

void OpenglRender::idleFunc()
{
    glutPostRedisplay();
}

void OpenglRender::keyboardFunc(unsigned char key, int x, int y)
{
    assert(currentRender);
    assert(currentRender->eventClient);
    currentRender->eventClient->process(
        currentRender->buildKeyboardEvent(key, glutGetModifiers(), x, y));
}

OpenglRender *OpenglRender::currentRender = NULL;

const int OpenglRender::width = 640;
const int OpenglRender::height = 480;
}
}
