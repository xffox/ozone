#ifndef RENDER_RENDER_H
#define RENDER_RENDER_H

namespace render
{
class Client;
class EventClient;

class Render
{
public:
    virtual ~Render(){}

    virtual void init(Client *client, EventClient *eventClient) = 0;
    virtual void destroy() = 0;
};
}

#endif
