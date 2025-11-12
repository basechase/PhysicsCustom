#pragma once
#include <cstdint>
#include "glm/vec2.hpp"


struct AABB
{
	glm::vec2 HalfExtents;
	float x;
	float y;
	float width  ;
	float height ;
	//dome
};

struct Circle 
{
	float Radius = 1.0f;

	
};

enum class ShapeType : uint8_t
{
	NONE = 0,
	CIRCLE = 1 << 0,
	AABB = 1 << 1
};

struct Shape
{
	ShapeType Type;
	
	union 
	{
		Circle CircleData;
		AABB AABBData;
	};
};
bool CheckCircleAABB(const glm::vec2& PosA, const Shape& ShapeA, const glm::vec2& PosB, const Shape& ShapeB);
bool CheckCircleAABB(const glm::vec2& PosA, const Circle& CircleA, const glm::vec2& PosB, const AABB& AABBB);
bool CheckCircleCircle(const glm::vec2& PosA, const Circle& CircleA, const glm::vec2& PosB, const Circle& CircleB);
bool CheckCircleCircle(const glm::vec2& PosA, const Shape& ShapeA, const glm::vec2& PosB, const Shape& ShapeB);
bool CheckAABBAABB(const glm::vec2& PosA, const AABB& AABBA, const glm::vec2& PosB, const AABB& AABBB);
bool CheckAABBAABB(const glm::vec2& PosA, const Shape& ShapeA, const glm::vec2& PosB, const Shape& ShapeB);