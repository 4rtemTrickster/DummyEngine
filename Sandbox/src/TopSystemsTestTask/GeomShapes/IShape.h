#pragma once
#include "Dummy.h"

/**
 * \brief Base class of geometric shapes
 */
class IShape
{
public:
    virtual ~IShape() = default;

    /**
     * \return Returns a smart pointer to a vertex array fully prepared for rendering
     */
    virtual Dummy::Ref<Dummy::VertexArray> GetVertexArray() = 0;

    /**
     * \brief The total number of children of this class. When creating a new child class, this variable must be incremented!
     */
    static constexpr size_t ChildCount = 4;

protected:
    Dummy::Ref<Dummy::VertexArray> VertexArray;
};
