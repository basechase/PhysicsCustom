#pragma once
#include <cstdint>
#include "glm/vec2.hpp"


struct AABB
{
	glm::vec2 HalfExtents;

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


/**
 * Calculates the minimum translation vector (MTV) to separate two circles
 *
 * @param PosA 			Position of the first circle
 * @param CircleA 		Shape of the first circle
 * @param PosB 			Position of the second circle
 * @param CircleB 		Shape of the second circle
 * @param Pen 			Output for penetration depth
 * @return glm::vec2 	Output for axis upon which they are to be separated along
 */
glm::vec2 DepenetrateCircleCircle(const glm::vec2& PosA, const Circle& CircleA, const glm::vec2& PosB, const Circle& CircleB, float& Pen);


/**
 * @brief Calculates the minimum translation vector (MTV) to separate two circles
 *
 * @param PosA 			Position of the first circle
 * @param ShapeA 		Shape of the first circle
 * @param PosB 			Position of the second circle
 * @param ShapeB 		Shape of the second circle
 * @param Pen 			Output for penetration depth
 * @return glm::vec2 	Output for axis upon which they are to be separated along
 */
glm::vec2 DepenetrateCircleCircle(const glm::vec2& PosA, const Shape& ShapeA, const glm::vec2& PosB, const Shape& ShapeB, float& Pen);