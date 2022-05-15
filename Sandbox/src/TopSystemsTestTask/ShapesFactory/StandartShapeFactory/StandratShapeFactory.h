#pragma once
#include "../IShapesFactory.h"
#include "../../GeomShapes/IShape.h"

class StandratShapeFactory : public IShapesFactory
{
public:
    StandratShapeFactory() = default;
    virtual ~StandratShapeFactory() = default;
    
    virtual void CreateShapes(std::vector<Dummy::Ref<IShape>>& Buffer) override;
};
