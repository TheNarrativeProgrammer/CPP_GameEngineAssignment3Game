#pragma once
#include "Actor.h"
#include "Game/Public/GameCore/GameCore.h"
#include "Engine/Public/EngineTypes.h"

class Ship : public Actor
{


public: 

	Ship() = delete;
	Ship(String shipName, exColor shipColor, exVector2 startingPos, exVector2 velocity);

	virtual void BeginPlay() override;

	void OnShipCollided(std::weak_ptr<Actor> HitActor, const exVector2& HitPosition);

	exVector2 mShipInitialVelocity;
	bool isGameOver = false;
private:

	String mShipName;
	exColor mShipColor;
	exVector2 mShipStartingPosition;
	


};

