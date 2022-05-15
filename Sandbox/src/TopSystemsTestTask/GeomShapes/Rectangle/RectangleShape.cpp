#include "RectangleShape.h"

RectangleShape::RectangleShape()
{
    VertexArray = Dummy::VertexArray::Create();

    std::array vertices =
    {
        -1.0f, -0.5f, -3.0f,
         1.0f, -0.5f, -3.0f,
         1.0f,  0.5f, -3.0f,
        -1.0f,  0.5f, -3.0f
    };

    Dummy::Ref<Dummy::VertexBuffer> VB = Dummy::VertexBuffer::Create(vertices.data(), sizeof(float) * vertices.size());

    VB->SetLayout(
    {
        {Dummy::ShaderDataType::FLOAT3, "a_Position"}
    });

    VertexArray->AddVertexBuffer(VB);

    std::array<uint32_t, 6> indices =
    {
        0, 1, 2,
        2, 3, 0
    };

    Dummy::Ref<Dummy::IndexBuffer> IB = Dummy::IndexBuffer::Create(indices.data(), indices.size());

    VertexArray->SetIndexBuffer(IB);
}
