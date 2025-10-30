#include <memory>
#include "World.h"
#include "PhysObject.h"
int main(void)
{
	auto App = std::make_unique<World>();

	App->InIt();

	PhysObject TestInst;

	while (!App->ShouldClose())
	{
		App->Tick();
		while (App->ShouldTickFixed())
		{
			App->TickFixed();
		}
		App->Draw();

	}
	App->Exit();

	return 0;
}