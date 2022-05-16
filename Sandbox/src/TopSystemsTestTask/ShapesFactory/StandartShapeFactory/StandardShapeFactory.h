#pragma once
#include "../IShapesFactory.h"


/**
 * \brief The factory responsible for generating a standard set of geometric shapes
 */
class StandardShapeFactory : public IShapesFactory
{
public:
    StandardShapeFactory() = default;
    virtual ~StandardShapeFactory() override = default;
    
    virtual void CreateShapes(std::vector<Dummy::Ref<IShape>>& Buffer) override;
};
