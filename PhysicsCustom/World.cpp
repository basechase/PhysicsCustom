#include "World.h"
#include "raylib.h"
#include "PhysObject.h"
#include "EnumUtils.h"
#include "iostream"
#include "unordered_map"
#include "Physics.h"
using CollisionFunc = bool (*)(const glm::vec2&, const Shape&, const glm::vec2&, const Shape&);
using CollisionMap = std::unordered_map<ShapeType, CollisionFunc>;
CollisionMap ColMap;
/** Function signature for resolution functions */
using DepenetrationFunc = glm::vec2(*)(const glm::vec2& PosA, const Shape& ShapeA, const glm::vec2& PosB, const Shape& ShapeB, float& Pen);
/** Map for associating pairs of collision shapes with their resolution functions */
using DepenetrationMap = std::unordered_map<ShapeType, DepenetrationFunc>;
DepenetrationMap DepenMap;
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
	ColMap[ShapeType::AABB | ShapeType::AABB] = CheckAABBAABB;
	ColMap[ShapeType::CIRCLE | ShapeType::AABB] = CheckCircleAABB;

	DepenMap[ShapeType::CIRCLE | ShapeType::CIRCLE] = DepenetrateCircleCircle;
	DepenMap[ShapeType::AABB | ShapeType::AABB] = DepenetrateCircleCircle;
	DepenMap[ShapeType::CIRCLE | ShapeType::AABB] = DepenetrateCircleCircle;

	OnInIt();
}

void World::Tick()
{

	AccumulatdFixedTime += GetFrameTime();
	OnTick();
}

void World::TickFixed()
{

	

	AccumulatdFixedTime -= TargetFixedStep;

	for (auto& PObj : PhysObjects)
	{
		
		PObj.AddAccel(Gravity);
		PObj.TickPhys(TargetFixedStep);

	}

			

	for (auto& i : PhysObjects)
	{
		
		for (auto& j : PhysObjects)
		{
			
			if (&i == &j) { continue; }
			
			if (i.MrShape.Type == ShapeType::NONE || j.MrShape.Type == ShapeType::NONE) { continue; }
			


			ShapeType ColKey = i.MrShape.Type | j.MrShape.Type;
			ShapeType PairType = i.MrShape.Type | j.MrShape.Type;
				float Pen = 0;

				glm::vec2 Normal = DepenMap[PairType](i.Pos, i.MrShape,
					j.Pos, j.MrShape, Pen);

			auto KeyPairIt = ColMap.find(ColKey);

			bool bHasFunc = KeyPairIt != ColMap.end();
			if (bHasFunc)
			{
				bool bIsColliding = false;

				PhysObject* First = &i;
				PhysObject* Second = &j;


				if (i.MrShape.Type > j.MrShape.Type)
				{
					bIsColliding = ColMap[ColKey](j.Pos, j.MrShape, i.Pos, i.MrShape);
				}
				else 
				{
					 bIsColliding = ColMap[ColKey](i.Pos, i.MrShape, j.Pos, j.MrShape);
				}
			
				if (bIsColliding)
				{
					std::cout << "collision!!" << std::endl;
					ResolvePhysObjects(i, j, 1.0f, Normal, Pen);
				}
				else 
				{
					std::cout << "UNABLE TO TEST FOR COLL/NO COLL FUNC DEFINED FOR THIS PAIR" << std::endl;
				}
			
			}
		}
	}
	OnTickFixed();
}

void World::Draw()
{
	for (auto& Object : PhysObjects)
	{
		Object.Draw();
	}

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





void World::OnInIt()
{
	
}

void World::OnTick()
{
	if (IsMouseButtonPressed(0)) 
	{
	PhysObject NewObj;
	NewObj.MrShape.Type = ShapeType::CIRCLE;
	NewObj.MrShape.CircleData.Radius = 25.0f;

	
	NewObj.Pos.x = GetMousePosition().x;
	NewObj.Pos.y = GetMousePosition().y;
	
	PhysObjects.push_back(NewObj);
	

	}

	if (IsMouseButtonPressed(1))
	{
		PhysObject NewObj;
		NewObj.MrShape.Type = ShapeType::AABB;
		

		NewObj.MrShape.AABBData.HalfExtents = { 30.0f, 25.0f };
		NewObj.Pos.x = GetMousePosition().x;
		NewObj.Pos.y = GetMousePosition().y;

		PhysObjects.push_back(NewObj);


	}

}