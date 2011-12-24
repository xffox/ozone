#include "render/KeyboardEvent.h"

namespace render
{

KeyboardEvent::KeyboardEvent(int key, unsigned char modifiers)
    :key(key), modifiers(modifiers)
{
}

}
