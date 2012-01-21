#ifndef OZONE_OBJECT_H
#define OZONE_OBJECT_H

#include <string>

namespace ozone
{
    class Object
    {
    public:
        virtual ~Object(){}

        virtual const std::string &getType() const = 0;
    };
}

#endif
