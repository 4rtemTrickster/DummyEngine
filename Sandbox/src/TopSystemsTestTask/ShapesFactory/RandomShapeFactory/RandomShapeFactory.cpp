#include "RandomShapeFactory.h"

#include "../../GeomShapes/Circle/CircleShape.h"
#include "../../GeomShapes/Rectangle/RectangleShape.h"
#include "../../GeomShapes/Square/SquareShape.h"
#include "../../GeomShapes/Triangle/TriangleShape.h"

void RandomShapeFactory::CreateShapes(std::vector<Dummy::Ref<IShape>>& Buffer)
{
    Buffer.clear();
    
    std::srand(std::time(nullptr));

    for (int i = 0; i < IShape::ChildCount; ++i)
    {
        int randNum = rand() % 4 + 1;

        switch (randNum)
        {
        case 1:
            Buffer.push_back(Dummy::CreateRef<CircleShape>());
            break;
        case 2:
            Buffer.push_back(Dummy::CreateRef<SquareShape>());
            break;
        case 3:
            Buffer.push_back(Dummy::CreateRef<TriangleShape>());
            break;
        case 4:
            Buffer.push_back(Dummy::CreateRef<RectangleShape>());
            break;
        }
    }
}
