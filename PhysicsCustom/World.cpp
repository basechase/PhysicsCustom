#include "World.h"
#include "raylib.h"
#include "PhysObject.h"
#include "EnumUtils.h"
#include "unordered_map"
using CollisionFunc = bool (*)(const glm::vec2&, const Shape&, const glm::vec2&, const Shape&);
using CollisionMap = std::unordered_map<ShapeType, CollisionFunc>;
CollisionMap ColMap;


World::World() : AccumulatdFixedTime(0), TargetFixedStep(1.0f/30), Gravity({0, 9.80665})
{
	
}

void World::InIt()
{
	
	ColMap[ShapeType::CIRCLE | ShapeType::CIRCLE] = CheckCircleCircle;
	const int screenWidth = 800;
	const int screenHeight = 450;
	
	PhysObject NewObj;
	NewObj.MrShape.Type = ShapeType::CIRCLE;
	NewObj.Pos = { 300,300 };
	NewObj.MrShape.CircleData.Radius = 10.0f;
	

	InitWindow(screenWidth, screenHeight, "raylib examp window");

	SetTargetFPS(60);
	OnInIt();
}

void World::Tick()
{

	AccumulatdFixedTime = GetFrameTime();
	OnTick();
}

void World::TickFixed()
{
	AccumulatdFixedTime += GetFrameTime();




	for (auto Object : PhysObjects)
	{
		Object.TickPhys(TargetFixedStep);
		
		if (Object.AllowPhys)
		{
			Object.Velocity -= Gravity;
		}
	}
	OnTick();
}

void World::Draw()
{
	BeginDrawing();

	ClearBackground(RAYWHITE);

	DrawText("FIRST WINDOW MADE", 190, 200, 20, LIGHTGRAY);

	OnDraw();

	EndDrawing();
}

void World::Exit()
{
	OnExit();
	CloseWindow();
}

bool World::ShouldClose() const
{
	return WindowShouldClose();
}

bool World::ShouldTickFixed() const
{
	return AccumulatdFixedTime >= TargetFixedStep;
}

