#pragma once
#include "../GeomShapes/IShape.h"

class IShapesFactory
{
public:
    virtual void CreateShapes(std::vector<Dummy::Ref<IShape>>& Buffer) = 0;
};
