#include "CircleShape.h"

#include <future>

#include "glm/ext/scalar_constants.hpp"

CircleShape::CircleShape()
{
    VertexArray = Dummy::VertexArray::Create();

    std::vector<float> vertices;

    // Circle center
    vertices.push_back(0.0f);   // X
    vertices.push_back(0.0f);   // Y
    vertices.push_back(-3.0f);  // Z

    // Coordinates of the bases of triangles
    for (size_t i = 0; i < SegmentsCount; ++i)
    {
        vertices.push_back(Radius * cos(i * 2.0f * glm::pi<float>() / SegmentsCount)); // X
        vertices.push_back(Radius * sin(i * 2.0f * glm::pi<float>() / SegmentsCount)); // Y
        vertices.push_back(-3.0f);  // Z
    }

    std::vector<uint32_t> indices;

    auto IndicesResult = std::async(std::launch::async, [&]
    {
        size_t i;
        size_t ind;
        for (i = 0, ind = 0; i <= vertices.size() / 3; ++i, ++ind)
        {
            if (indices.size() != 0 && indices.size() % 3 == 0)
            {
                indices.push_back(0);
                indices.push_back(i - 1);
                ind = 0;
            }

            indices.push_back(i);
        }
        *(indices.end() - 1) = 1;
    });

    Dummy::Ref<Dummy::VertexBuffer> VB = Dummy::VertexBuffer::Create(vertices.data(), sizeof(float) * vertices.size());

    VB->SetLayout(
        {
            {Dummy::ShaderDataType::FLOAT3, "a_Position"}
        });

    VertexArray->AddVertexBuffer(VB);

    IndicesResult.wait();

    Dummy::Ref<Dummy::IndexBuffer> IB = Dummy::IndexBuffer::Create(indices.data(), indices.size());

    VertexArray->SetIndexBuffer(IB);
}
