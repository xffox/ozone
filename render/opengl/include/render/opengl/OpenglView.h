#ifndef RENDER_OPENGL_OPENGL_VIEW_H
#define RENDER_OPENGL_OPENGL_VIEW_H

#include <memory>

#include "render/View.h"

namespace render
{
    class Client;

    namespace opengl
    {
    class OpenglDrawer;

    class OpenglView: public View
    {
    public:
        OpenglView();
        virtual ~OpenglView();

        virtual std::auto_ptr<LightDrawer> createLightDrawer();

        void init(Client *client);
        void destroy();
        bool isInited() const;

        void draw();

    private:
        OpenglView(const OpenglView&);
        OpenglView &operator=(const OpenglView&);

        void prepare();
        void cleanup();
        
    private:
        Client *client;
        std::auto_ptr<OpenglDrawer> drawer;
    };
    }
}

#endif
