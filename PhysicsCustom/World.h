#pragma once
class World
{
public:


	float TargetFixedStep;

	World();
	// For initialization
	void InIt();

	// for update logic
	void Tick();


	// for physics update logic
	void TickFixed();

	// for drawing
	void Draw();

	//for cleanup/termination
	void Exit();

	//signals shutdown
	bool ShouldClose() const;

	//return true if needs tickfixed, otherwise false
	bool ShouldTickFixed() const;

protected:

	float AccumulatdFixedTime;

	// runs at end of init
	virtual void OnInIt() {};

	//runs on end of tick
	virtual void OnTick() {};

	// runs at end of darw
	virtual void OnDraw() const {};

	//runs on start of exit
	virtual void OnExit() {};




};

