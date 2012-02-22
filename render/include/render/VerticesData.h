#ifndef RENDER_VERTICES_DATA_H
#define RENDER_VERTICES_DATA_H

#include <cstddef>

#include "util/typed/TypedStrideVector.h"

namespace geom
{
    class Point;
}

namespace render
{
    class VerticesData
    {
    public:
        VerticesData();

        void resize(std::size_t size);
        std::size_t size() const;

        void SetVertex(std::size_t index, const geom::Point& vertex);
        void SetNormal(std::size_t index, const geom::Point& normal);

    private:
        util::typed::TypedStrideVector vertices;
        util::typed::TypedStrideVector normals;
        util::typed::TypedStrideVector colors;
    };
}

#endif
