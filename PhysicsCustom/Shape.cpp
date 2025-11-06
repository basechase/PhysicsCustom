#include "Shape.h"
#include <cmath>
#include <cassert>
#include <glm//glm.hpp>
bool CheckCircleCircle(const glm::vec2& PosA, const Circle& CircleA, const glm::vec2& PosB, const Circle& CircleB)
{


    glm::vec2 Offset = PosA - PosB;
    float Dist = glm::length(Offset);

    float Sum = CircleA.Radius + CircleB.Radius;

    return Dist < Sum;
}


  
bool CheckCircleAABBAABB(const glm::vec2& PosA, const AABB& AABBA, const glm::vec2& PosB, const AABB& AABBB)
{
    float DistX = PosA.x - glm::clamp(PosA.x, PosB.x - AABBB.HalfExtents.x, PosB.x + AABBB.HalfExtents.x);
    float DistY = PosA.y - glm::clamp(PosA.y, PosB.y - AABBB.HalfExtents.y, PosB.y + AABBB.HalfExtents.y);

    return false;
}

bool CheckCircleCircle(const glm::vec2& PosA, const Shape& ShapeA, const glm::vec2& PosB, const Shape& ShapeB)
{
    assert(ShapeA.Type == ShapeType::CIRCLE && "Called CheckCircleCircle but a circle was not provided!!");
    assert(ShapeB.Type == ShapeType::CIRCLE && "Called CheckCircleCircle but a circle was not provided!!");
    
    return CheckCircleCircle(PosA, ShapeA.CircleData, PosB, ShapeB.CircleData);
}

bool CheckAABBAABB(const glm::vec2& PosA, const AABB& AABBA, const glm::vec2& PosB, const AABB& AABBB)
{

    return PosA.x - AABBA.HalfExtents.x < PosB.x + AABBB.HalfExtents.x &&
           PosA.x - AABBA.HalfExtents.x < PosB.x + AABBB.HalfExtents.x &&
           PosA.y - AABBA.HalfExtents.y < PosB.y + AABBB.HalfExtents.y &&
           PosA.y - AABBA.HalfExtents.y < PosB.y + AABBB.HalfExtents.y;
}

