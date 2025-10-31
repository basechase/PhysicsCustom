#pragma once
#include <cstdint>
#include "glm/vec2.hpp"


struct Circle 
{
	float Radius;
};

enum class ShapeType : uint8_t
{
	NONE = 0,
	CIRCLE = 1 <<0,
	AABB = 1 << 1
};

struct Shape
{
	ShapeType Type;
	
	union 
	{
		Circle CircleData;
	};
};

bool CheckCircleCircle(const glm::vec2& PosA, const Circle& CircleA, const glm::vec2& PosB, const Circle& CircleB);
bool CheckCircleCircle(const glm::vec2& PosA, const Shape& ShapeA, const glm::vec2& PosB, const Shape& ShapeB);

