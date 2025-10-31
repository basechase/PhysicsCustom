#include "Shape.h"
#include <cmath>
bool CheckCircleCircle(const glm::vec2& PosA, const Circle& CircleA, const glm::vec2& PosB, const Circle& CircleB)
{
    float distX = PosA.x - PosB.x;
    float distY = PosA.y - PosB.y;
    float distance = sqrt((distX * distX) + (distY * distY));
    float SumRadi = CircleA.Radius + CircleB.Radius;

    if (distance < SumRadi)
    {
        return true;
    }

    return false;
}

bool CheckCircleCircle(const glm::vec2& PosA, const Shape& ShapeA, const glm::vec2& PosB, const Shape& ShapeB)
{
    return CheckCircleCircle(PosA, ShapeA.CircleData, PosB, ShapeB.CircleData);
}

