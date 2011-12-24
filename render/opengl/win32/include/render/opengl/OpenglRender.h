#ifndef RENDER_OPENGL_OPENGL_RENDER_H
#define RENDER_OPENGL_OPENGL_RENDER_H

#include <memory>
#include <windows.h>

#include "util/Runnable.h"
#include "render/Render.h"
#include "render/opengl/View.h"

namespace util
{
    class Thread;
}

namespace render
{
    class Client;

    namespace opengl
    {
    class OpenglRender: public Render
    {
        class MainLoopRunnable: public util::Runnable
        {
        public:
            virtual void run();
        };

    public:
        OpenglRender();
        virtual ~OpenglRender();

        virtual void init(Client *client);
        virtual void destroy();

    private:
        void prepare();
        void cleanup();
        BOOL createWindow(const char *title, int width, int height);
        void destroyWindow();

    private:
        static LRESULT CALLBACK wndProc(HWND windowHandler, UINT msg,
            WPARAM wParam, LPARAM lParam);
        static void mainLoop();
        static void renderFunc();

    private:
        MainLoopRunnable mainLoopRunnable;
        std::auto_ptr<util::Thread> mainLoopThread;

        Client *client;
        View view;

        HINSTANCE appInstanceHandler;
        HGLRC renderContextHandler;
        HDC deviceContextHandler;
        HWND windowHandler;

    private:
        static OpenglRender *currentRender;

        static const int width;
        static const int height;

        static const char *const windowClassName;
    };
    }
}

#endif
