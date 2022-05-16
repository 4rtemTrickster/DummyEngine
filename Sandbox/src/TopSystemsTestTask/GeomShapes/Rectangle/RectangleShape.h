#pragma once
#include "../IShape.h"

class RectangleShape : public IShape
{
public:
    RectangleShape();
    
    Dummy::Ref<Dummy::VertexArray> GetVertexArray() override { return VertexArray; }
};
