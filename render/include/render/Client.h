#ifndef RENDER_CLIENT_H
#define RENDER_CLIENT_H

namespace render
{
    class Drawer;
    class View;

    class Client
    {
    public:
        virtual ~Client(){}

        virtual void init(View *view) = 0;
        virtual void destroy() = 0;
        virtual void draw(Drawer *drawer) = 0;
    };
}

#endif
