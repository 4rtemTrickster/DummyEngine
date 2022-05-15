#include "StandratShapeFactory.h"

#include "../../GeomShapes/Circle/CircleShape.h"
#include "../../GeomShapes/Rectangle/RectangleShape.h"
#include "../../GeomShapes/Square/SquareShape.h"
#include "../../GeomShapes/Triangle/TriangleShape.h"

void StandratShapeFactory::CreateShapes(std::vector<Dummy::Ref<IShape>>& Buffer)
{
    Buffer.clear();

    Buffer.push_back(Dummy::CreateRef<CircleShape>());
    Buffer.push_back(Dummy::CreateRef<SquareShape>());
    Buffer.push_back(Dummy::CreateRef<TriangleShape>());
    Buffer.push_back(Dummy::CreateRef<RectangleShape>());
    
}
