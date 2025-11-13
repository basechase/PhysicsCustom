#pragma once
#include "glm/glm.hpp"
#include "glm/vec2.hpp"
#include "World.h"
#include "Shape.h"

class PhysObject
{
public:
	glm::vec2 Pos;
	glm::vec2 Velocity;
	glm::vec2 Accumulated;
	glm::vec2 Acceleration;

	Shape MrShape;
	bool AllowPhys;
	float mass;

	
	
	PhysObject();

	void Draw() const;


	void AddImpulse(glm::vec2 Vector);

	void AddVelocity(glm::vec2 Vector);

	void AddAccel(glm::vec2 Vector);

	void AddForce(glm::vec2 Vector);

	void TickPhys(float Delta);

protected:
	float Gravity = 9.81f;
};

