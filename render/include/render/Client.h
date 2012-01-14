#ifndef RENDER_CLIENT_H
#define RENDER_CLIENT_H

namespace render
{
    class Drawer;

    class Client
    {
    public:
        virtual ~Client(){}

        virtual void init() = 0;
        virtual void destroy() = 0;
        virtual void draw(Drawer *drawer) = 0;
    };
}

#endif
