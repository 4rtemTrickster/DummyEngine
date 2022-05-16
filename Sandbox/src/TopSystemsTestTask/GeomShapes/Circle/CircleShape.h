#pragma once
#include "../IShape.h"

class CircleShape : public IShape
{
public:
    CircleShape();
    ~CircleShape() override {}
    
    Dummy::Ref<Dummy::VertexArray> GetVertexArray() override { return VertexArray; }

protected:

    const size_t SegmentsCount = 100;
    const float Radius = 0.5f;
};
