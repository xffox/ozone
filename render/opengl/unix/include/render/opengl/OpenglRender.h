#ifndef RENDER_OPENGL_OPENGL_RENDER_H
#define RENDER_OPENGL_OPENGL_RENDER_H

#include <memory>

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
    class KeyboardEvent;

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

        virtual void init(Client *client, EventClient *eventClient);
        virtual void destroy();

    private:
        OpenglRender(const OpenglRender&);
        OpenglRender &operator=(const OpenglRender&);

        void prepare();
        KeyboardEvent buildKeyboardEvent(unsigned char key, int modifiers,
            int x, int y);

    private:
        static void renderFunc();
        static void idleFunc();
        static void keyboardFunc(unsigned char key, int x, int y);
        static void motionFunc(int x, int y);

    private:
        MainLoopRunnable mainLoopRunnable;
        std::auto_ptr<util::Thread> mainLoopThread;

        Client *client;
        EventClient *eventClient;
        View view;

    private:
        static OpenglRender *currentRender;

        static const int width;
        static const int height;
    };
    }
}

#endif
