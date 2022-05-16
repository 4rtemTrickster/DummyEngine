#pragma once
#include "../GeomShapes/IShape.h"

/**
 * \brief The base class of the factory responsible for generating a set of geometric shapes
 */
class IShapesFactory
{
public:
    virtual ~IShapesFactory() = default;
    
    /**
     * \brief Creates a set of geometric shapes to draw
     * \param Buffer A buffer for storing smart pointers to generated geometric shapes. <p>Warning: Buffer will be flushed before generating new shapes
     */
    virtual void CreateShapes(std::vector<Dummy::Ref<IShape>>& Buffer) = 0;
};
