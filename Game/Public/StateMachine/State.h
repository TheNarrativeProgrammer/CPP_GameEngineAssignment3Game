#pragma once
#include "Game/Public/GameCore/GameCore.h"
#include "Game/Public/Actors/Actor.h"
#include "Game/Public/Actors/Ship.h"

class Ship;
template <class SateDependencyObject>

class State
{

public:
	State() 
	{
		mNextState = "";
	};
	
	State(String NextState) {
		mNextState = NextState;
	};

	virtual ~State() {}; // required to use a dynamic cast on a class. at least one virtual method


	// State Methods
	virtual void Enter(std::shared_ptr<SateDependencyObject> DependencyObject) = 0;
	virtual void Update(std::shared_ptr<SateDependencyObject> DependencyObject) = 0;
	virtual void Exit(std::shared_ptr<SateDependencyObject> DependencyObject) = 0;

	void SetNextState(const String& NextState)
	{
		mNextState = NextState;
	};

	String GetNextState() const 
	{
		return mNextState;
	};

private:

	String mNextState;

};

class MainMenu : public State<Actor>
{
public:

	MainMenu() 
	{
		SetNextState("GamePlay");
	}

	virtual void Enter(std::shared_ptr<Actor> DependencyObject) override 
	{
		PlayButton = std::make_shared<Actor>();
		PlayButton->AddComponentOfType<TransformComponent>(exVector2(500.0f, 500.0f));
		PlayButton->AddComponentOfType<BoxRenderComponent>(125.0f, 50.0f, exColor({255,0,255,255}));
		PlayButton->AddComponentOfType<BoxColliderComponent>(125.0f, 50.0f, exVector2({0.0f, -1.5f}));

		QuitButton = std::make_shared<Actor>();
		QuitButton->AddComponentOfType<TransformComponent>(exVector2(500.0f, 250.0f));
		QuitButton->AddComponentOfType<BoxRenderComponent>(125.0f, 50.0f, exColor({ 255,0,255,255 }));
		QuitButton->AddComponentOfType<CircleColliderComponent>(90.0f, exVector2({ 0.0f, 1.5f }));
	}

	virtual void Update(std::shared_ptr<Actor> DependencyObject) override
	{

	}

	virtual void Exit(std::shared_ptr<Actor> DependencyObject) override
	{
		PlayButton.reset();
		QuitButton.reset();
	}

private:

	std::shared_ptr<Actor> PlayButton;
	std::shared_ptr<Actor> QuitButton;
};

class Gameplay : public State<Actor>
{
public:

	Gameplay()
	{
		SetNextState("EndGame");
	}

	virtual void Enter(std::shared_ptr<Actor> DependencyObject) override
	{
		Player = std::make_shared<Ship>("Player Ship", exColor({ 150,20,30,255 }), exVector2(50.0f, 300.0f), exVector2(0.2f, 0.0f));
		Player->BeginPlay();
	}

	virtual void Update(std::shared_ptr<Actor> DependencyObject) override
	{

	}

	virtual void Exit(std::shared_ptr<Actor> DependencyObject) override
	{
		Player.reset();
	}

private:

	std::shared_ptr<Actor> Player;
};

class EndGame : public State<Actor>
{
public:

	EndGame()
	{
		SetNextState("MainMenu");
	}

	virtual void Enter(std::shared_ptr<Actor> DependencyObject) override
	{
		RetryButton = std::make_shared<Actor>();
		RetryButton->AddComponentOfType<TransformComponent>(exVector2(500.0f, 500.0f));
		RetryButton->AddComponentOfType<BoxRenderComponent>(125.0f, 50.0f, exColor({ 255,0,255,255 }));
	}

	virtual void Update(std::shared_ptr<Actor> DependencyObject) override
	{

	}

	virtual void Exit(std::shared_ptr<Actor> DependencyObject) override
	{

	}

private:

	std::shared_ptr<Actor> RetryButton;
};
