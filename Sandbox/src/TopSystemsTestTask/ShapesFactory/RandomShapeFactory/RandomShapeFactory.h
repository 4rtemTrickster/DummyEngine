#pragma once
#include "../IShapesFactory.h"
#include "../../GeomShapes/IShape.h"

/**
 * \brief The factory responsible for generating a random set of geometric shapes
 */
class RandomShapeFactory : public IShapesFactory
{
public:
    RandomShapeFactory() = default;
    virtual ~RandomShapeFactory() override = default;

    virtual void CreateShapes(std::vector<Dummy::Ref<IShape>>& Buffer) override;
};
