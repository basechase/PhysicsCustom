#pragma once
#include "glm/vec2.hpp"
#include "World.h"

class PhysObject
{
public:
	glm::vec2 Pos;
	glm::vec2 Velocity;
	World* World;

	bool AllowPhys;
	glm::vec2 Accumulated;
	glm::vec2 Acceleration;
	float mass;


	PhysObject();

	void AddImpulse(glm::vec2 Vector);

	void AddVelocity(glm::vec2 Vector);

	void AddAccel(glm::vec2 Vector);

	void AddForce(glm::vec2 Vector);

	void TickPhys(float Delta);

protected:
	float Gravity = 9.81f;
};

