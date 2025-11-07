#include "PhysObject.h"
#include "raylib.h"
const float TARGET_FIXED_TIME_STEP = 1.0f / 30.0f;

PhysObject::PhysObject() : 
	Pos({ 0,0 }),
	Velocity({ 0,0 }),
	mass(10.f),
	MrShape({ ShapeType::NONE }),
	AllowPhys(true),
	Accumulated({ 0,0 })
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
		DrawCircle(Pos.x, Pos.y, MrShape.CircleData.Radius, RED);
		break;
	case ShapeType::AABB:
		DrawRectangle(Pos.x, Pos.y, 10, 10, RED);
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
	Velocity += Vector * TARGET_FIXED_TIME_STEP;
}

void PhysObject::AddForce(glm::vec2 Vector)
{

	Acceleration += Vector / mass;

}

void PhysObject::TickPhys(float Delta)
{
	Velocity += Accumulated;
	Accumulated = { };

	Pos += Velocity * Delta;
}
