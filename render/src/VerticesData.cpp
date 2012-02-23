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
    vertices.resize<float>(size);
    normals.resize<float>(size);
    colors.resize<float>(size);
}

std::size_t VerticesData::size() const
{
    return vertices.size();
}

}
