#include "render/opengl/OpenglRender.h"

#include "util/Thread.h"
#include "render/Client.h"

namespace render
{
namespace opengl
{
void OpenglRender::MainLoopRunnable::run()
{
    currentRender->prepare();

    currentRender->view.init(currentRender->client);

    currentRender->mainLoop();

    currentRender->view.destroy();

    currentRender->cleanup();
}

OpenglRender::OpenglRender()
    :mainLoopThread(new util::Thread),
    client(NULL),
    appInstanceHandler(NULL), renderContextHandler(NULL),
    deviceContextHandler(NULL), windowHandler(NULL)
{
    appInstanceHandler = GetModuleHandle(NULL);
}

OpenglRender::~OpenglRender()
{
#if 0
    destroy();
#endif
}

void OpenglRender::init(Client *client)
{
    if(!client)
        throw std::exception();
    if(currentRender)
        throw std::exception();

    this->client = client;
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
    if(createWindow("ozone", width, height))
        throw std::exception();
}

void OpenglRender::cleanup()
{
    destroyWindow();
}

BOOL OpenglRender::createWindow(const char *title, int width, int height)
{
    RECT windowRect;
    windowRect.left = 0;
    windowRect.right = width;
    windowRect.top = 0;
    windowRect.bottom = height;

    WNDCLASS windowClass;
    // redraw on move, own DC for window
    windowClass.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC; 
    windowClass.lpfnWndProc = wndProc;
    windowClass.cbClsExtra = 0;
    windowClass.cbWndExtra = 0;
    windowClass.hInstance = appInstanceHandler;
    windowClass.hIcon = LoadIcon(NULL, IDI_WINLOGO);
    windowClass.hCursor = LoadCursor(NULL, IDC_ARROW);
    windowClass.hbrBackground = NULL;
    windowClass.lpszMenuName = NULL;
    windowClass.lpszClassName = windowClassName;
    if(!RegisterClass(&windowClass))
    {
        return false;
    }

    DWORD windowExtStyle = WS_EX_APPWINDOW | WS_EX_WINDOWEDGE;
    DWORD windowStyle = WS_OVERLAPPEDWINDOW;

    AdjustWindowRectEx(&windowRect, windowStyle, FALSE, windowExtStyle);

    if(!(windowHandler = CreateWindowEx(windowExtStyle, windowClassName,
                title, WS_CLIPSIBLINGS | WS_CLIPCHILDREN | windowStyle,
                0, 0, windowRect.right - windowRect.left,
                windowRect.bottom - windowRect.top,
                NULL, NULL, appInstanceHandler, NULL)))
    {
        destroyWindow();
        return false;
    }

    if(!(deviceContextHandler = GetDC(windowHandler)))
    {
        destroyWindow();
        return false;
    }

    if(!(renderContextHandler = wglCreateContext(deviceContextHandler)))
    {
        destroyWindow();
        return false;
    }

    if(!wglMakeCurrent(deviceContextHandler, renderContextHandler))
    {
        destroyWindow();
        return false;
    }

    ShowWindow(windowHandler, SW_SHOW);
    SetForegroundWindow(windowHandler);
    SetFocus(windowHandler);

    return true;
}

void OpenglRender::destroyWindow()
{
    if(renderContextHandler)
    {
        if(!wglMakeCurrent(NULL, NULL)) // release DC and RC contexts
        {
            // TODO: log
        }
        if(!wglDeleteContext(renderContextHandler))
        {
            // TODO: log
        }
        renderContextHandler = NULL;
    }

    if(deviceContextHandler)
    {
        if(!ReleaseDC(windowHandler, deviceContextHandler))
        {
            // TODO: log
        }
        deviceContextHandler = NULL;
    }

    if(windowHandler)
    {
        if(!DestroyWindow(windowHandler))
        {
            // TODO: log
        }
        windowHandler = NULL;
    }

    if(!UnregisterClass(windowClassName, appInstanceHandler))
    {
        // TODO: log
    }
}

LRESULT CALLBACK OpenglRender::wndProc(HWND windowHandler, UINT msg,
    WPARAM wParam, LPARAM lParam)
{
    switch(msg)
    {
    case WM_ACTIVATE:
        break;
    case WM_CLOSE:
        PostQuitMessage(0);
        return 0;
    }

    return DefWindowProc(windowHandler, msg, wParam, lParam);
}

void OpenglRender::mainLoop()
{
    bool run = true;
    MSG msg;
    while(run)
    {
        if(PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
        {
            if(WM_QUIT == msg.message)
            {
                run = false;
            }
            else
            {
                TranslateMessage(&msg);
                DispatchMessage(&msg);
            }
        }
        else
        {
            renderFunc();
        }
    }
}

void OpenglRender::renderFunc()
{
    currentRender->view.draw();
    SwapBuffers(currentRender->deviceContextHandler);
}

OpenglRender *OpenglRender::currentRender = NULL;

const int OpenglRender::width = 640;
const int OpenglRender::height = 480;
const char *const OpenglRender::windowClassName = "OpenGL";
}
}
