#pragma once
#include "../IShapesFactory.h"
#include "../../GeomShapes/IShape.h"

class RandomShapeFactory : public IShapesFactory
{
public:
    RandomShapeFactory() = default;
    virtual ~RandomShapeFactory() = default;

    virtual void CreateShapes(std::vector<Dummy::Ref<IShape>>& Buffer) override;
};
