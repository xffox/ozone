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

        template<typename T>
        util::typed::TypedStrideVector::Reference<T> getVertex(
            std::size_t index);
        template<typename T>
        util::typed::TypedStrideVector::ConstReference<T> getVertex(
            std::size_t index) const;

        template<typename T>
        util::typed::TypedStrideVector::Reference<T> getNormal(
            std::size_t index);
        template<typename T>
        util::typed::TypedStrideVector::ConstReference<T> getNormal(
            std::size_t index) const;

        template<typename T>
        util::typed::TypedStrideVector::Reference<T> getColor(
            std::size_t index);
        template<typename T>
        util::typed::TypedStrideVector::ConstReference<T> getColor(
            std::size_t index) const;

    private:
        util::typed::TypedStrideVector vertices;
        util::typed::TypedStrideVector normals;
        util::typed::TypedStrideVector colors;
    };

    template<typename T>
    util::typed::TypedStrideVector::Reference<T> VerticesData::getVertex(
        std::size_t index)
    {
        return vertices.at<T>(index);
    }

    template<typename T>
    util::typed::TypedStrideVector::ConstReference<T> VerticesData::getVertex(
        std::size_t index) const
    {
        return vertices.at<T>(index);
    }

    template<typename T>
    util::typed::TypedStrideVector::Reference<T> VerticesData::getNormal(
        std::size_t index)
    {
        return normals.at<T>(index);
    }

    template<typename T>
    util::typed::TypedStrideVector::ConstReference<T> VerticesData::getNormal(
        std::size_t index) const
    {
        return normals.at<T>(index);
    }

    template<typename T>
    util::typed::TypedStrideVector::Reference<T> VerticesData::getColor(
        std::size_t index)
    {
        return colors.at<T>(index);
    }

    template<typename T>
    util::typed::TypedStrideVector::ConstReference<T> VerticesData::getColor(
        std::size_t index) const
    {
        return colors.at<T>(index);
    }
}

#endif
