#pragma once
#include "../IShape.h"
#include "Dummy.h"

class SquareShape : public IShape
{
public:
    SquareShape();
    ~SquareShape() override {}
    
    Dummy::Ref<Dummy::VertexArray> GetVertexArray() override { return VertexArray; }
};
