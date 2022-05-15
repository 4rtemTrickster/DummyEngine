#pragma once
#include "../IShape.h"

class TriangleShape : public IShape
{
public:
    TriangleShape();
    
    Dummy::Ref<Dummy::VertexArray> GetVertexArray() override { return VertexArray;}
};
