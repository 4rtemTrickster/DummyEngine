#pragma once
#include "Dummy.h"

class IShape
{
public:
    virtual ~IShape() = default;

    virtual Dummy::Ref<Dummy::VertexArray> GetVertexArray() = 0;

    static constexpr size_t ChildCount = 4;

protected:

    Dummy::Ref<Dummy::VertexArray> VertexArray;
    
};
