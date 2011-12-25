#ifndef RENDER_OPENGL_VIEW_H
#define RENDER_OPENGL_VIEW_H

#include "render/opengl/OpenglDrawer.h"

namespace render
{
    class Client;

    namespace opengl
    {
    class View
    {
    public:
        View();
        ~View();

        void init(Client *client);
        void destroy();
        bool isInited() const;

        void draw();

    private:
        View(const View&);
        View &operator=(const View&);

        void prepare();
        
    private:
        Client *client;
        OpenglDrawer drawer;
    };
    }
}

#endif
