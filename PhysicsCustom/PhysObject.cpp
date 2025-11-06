#include "PhysObject.h"
#include "raylib.h"

PhysObject::PhysObject() : Pos({0,0}), Velocity({0,0}), mass(10.f), MrShape({ShapeType::NONE})
{

}



void PhysObject::Draw() const
{
	
	switch (MrShape.Type)
	{
	case ShapeType::NONE:
		DrawPixel(Pos.x, Pos.y, RED);
		break;
	case ShapeType::CIRCLE:
		DrawCircle(Pos.x, Pos.y, 10, RED);
		break;
	case ShapeType::AABB:
		break;
	default:
		break;
	}
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
