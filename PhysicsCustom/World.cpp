#include "World.h"
#include "raylib.h"
#include "PhysObject.h"
#include "EnumUtils.h"
#include "iostream"
#include "unordered_map"
using CollisionFunc = bool (*)(const glm::vec2&, const Shape&, const glm::vec2&, const Shape&);
using CollisionMap = std::unordered_map<ShapeType, CollisionFunc>;
CollisionMap ColMap;


World::World() : AccumulatdFixedTime(0), TargetFixedStep(1.0f/30), Gravity({0, 9.80665})
{
	
}

void World::InIt()
{
	const int screenWidth = 800;
	const int screenHeight = 450;
	
	InitWindow(screenWidth, screenHeight, "raylib examp window");
	
	SetTargetFPS(60);
	ColMap[ShapeType::CIRCLE | ShapeType::CIRCLE] = CheckCircleCircle;
	
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

	for (auto& i : PhysObjects)
	{
		for (auto& j : PhysObjects)
		{
			if (&i == &j) { continue; }
			
			if (i.MrShape.Type == ShapeType::NONE || j.MrShape.Type == ShapeType::NONE) { continue; }

			ShapeType ColKey = i.MrShape.Type | j.MrShape.Type;

			bool bIsColliding = ColMap[ColKey](i.Pos, i.MrShape, j.Pos, j.MrShape);
			if (bIsColliding)
			{
				std::cout << "collision!!" << std::endl;
			}
		}
	}


	for (auto& Object : PhysObjects)
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

void World::OnTick()
{
	if (IsMouseButtonPressed(0))
	{
		PhysObject NewObj;
		NewObj.MrShape.Type = ShapeType::CIRCLE;
		NewObj.MrShape.CircleData.Radius = 25.0f;
		NewObj.Pos = { 300,300 };
		PhysObjects.push_back(NewObj);

		Vector2 CurMouse = GetMousePosition();
		NewObj.Pos.x = CurMouse.x;
		NewObj.Pos.y = CurMouse.y;
	}
}