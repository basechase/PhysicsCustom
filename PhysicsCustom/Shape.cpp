#include "Shape.h"
#include <cmath>
#include <cassert>
#include <glm//glm.hpp>
bool CheckCircleCircle(const glm::vec2& PosA, const Circle& CircleA, const glm::vec2& PosB, const Circle& CircleB)
{
    float distX = PosA.x - PosB.x;
    float distY = PosA.y - PosB.y;

    float d = sqrt((distX * distX) + (distY * distY));

    if (d <= CircleA.Radius + CircleB.Radius)
    {
        return true;
    }
    else
    {
        return false;
    }

}


  
bool CheckCircleAABB(const glm::vec2& PosA, const Shape& ShapeA, const glm::vec2& PosB, const Shape& ShapeB)
{
    assert(ShapeA.Type == ShapeType::CIRCLE && "Called CheckCircleAABB but a Circle was not provided! for shape 1");
    assert(ShapeB.Type == ShapeType::AABB && "Called CheckCircleAABB but an AABB was not provided! for shape 2");

    return CheckCircleAABB(PosA, ShapeA.CircleData, PosB, ShapeB.AABBData);
}

bool CheckCircleAABB(const glm::vec2& PosA, const Circle& CircleA, const glm::vec2& PosB, const AABB& AABBB)
{
    float DistX = PosA.x - glm::clamp(PosA.x, PosB.x - AABBB.HalfExtents.x, PosB.x + AABBB.HalfExtents.x);
    float DistY = PosA.y - glm::clamp(PosA.y, PosB.y - AABBB.HalfExtents.y, PosB.y + AABBB.HalfExtents.y);

    return (DistX * DistX + DistY + DistY) < CircleA.Radius * CircleA.Radius;
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
           PosA.x + AABBA.HalfExtents.x > PosB.x - AABBB.HalfExtents.x &&
           PosA.y - AABBA.HalfExtents.y < PosB.y + AABBB.HalfExtents.y &&
           PosA.y + AABBA.HalfExtents.y > PosB.y - AABBB.HalfExtents.y;
}

bool CheckAABBAABB(const glm::vec2& PosA, const Shape& ShapeA, const glm::vec2& PosB, const Shape& ShapeB)
{
    assert(ShapeA.Type == ShapeType::AABB && "Called CheckAABBAABB but an AABB was not provided!");
    assert(ShapeB.Type == ShapeType::AABB && "Called CheckAABBAABB but an AABB was not provided!");

    return CheckAABBAABB(PosA, ShapeA.AABBData, PosB, ShapeB.AABBData);
}

glm::vec2 DepenetrateCircleCircle(const glm::vec2& PosA, const Circle& CircleA, const glm::vec2& PosB, const Circle& CircleB, float& Pen)
{
    /** Get the distance between the two circles */
    float Dist = glm::length(PosB - PosA);
    /** Add up the sum of the two radii */
    float Radii = CircleA.Radius + CircleB.Radius;

    /** Find the difference and write it to the referenced variable */
    Pen = Radii - Dist;

    /** Return the direction to correct along */
    return glm::normalize(PosB - PosA);
}

glm::vec2 DepenetrateCircleCircle(const glm::vec2& PosA, const Shape& ShapeA, const glm::vec2& PosB, const Shape& ShapeB, float& Pen)
{
    return DepenetrateCircleCircle(PosA, ShapeA, PosB, ShapeB, Pen);
}

