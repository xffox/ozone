#include "render/VerticesData.h"

#include "geom/Point.h"

namespace render
{
VerticesData::VerticesData()
    :vertices(util::typed::TypedStrideVector::create<float>(3)),
    normals(util::typed::TypedStrideVector::create<float>(3)),
    colors(util::typed::TypedStrideVector::create<float>(3))
{
}

void VerticesData::resize(std::size_t size)
{
    vertices.resize(size);
#if 0
    normals.resize(size);
    colors.resize(size);
#endif
}

std::size_t VerticesData::size() const
{
    return vertices.size();
}

void VerticesData::SetVertex(std::size_t index, const geom::Point& vertex)
{
    util::typed::TypedStrideVector::Reference<float> ref =
        vertices.at<float>(index);
    ref[0] = vertex.x;
    ref[1] = vertex.y;
    ref[2] = vertex.z;
}

void VerticesData::SetNormal(std::size_t index, const geom::Point& normal)
{
}

}
