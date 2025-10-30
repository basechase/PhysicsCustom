#include "World.h"
#include "raylib.h"

World::World() : AccumulatdFixedTime(0), TargetFixedStep(1.0f/30)
{

}



void World::InIt()
{
	const int screenWidth = 800;
	const int screenHeight = 450;

	InitWindow(screenWidth, screenHeight, "raylib examp woindow");

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

