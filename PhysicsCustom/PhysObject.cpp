#include "PhysObject.h"


PhysObject::PhysObject() : Pos({0,0}), Velocity({0,0}), mass(10.f)
{

}

void PhysObject::AddImpulse(glm::vec2 Vector)
{
	
}

void PhysObject::AddVelocity(glm::vec2 Vector)
{
	Velocity += Vector;
}

void PhysObject::AddAccel(glm::vec2 Vector)
{
	Acceleration += Vector;
}

void PhysObject::AddForce(glm::vec2 Vector)
{

	Acceleration += Vector / mass;

}

void PhysObject::TickPhys(float Delta)
{
	Velocity += Acceleration * Delta;
	Acceleration = { 0,0 };
}
