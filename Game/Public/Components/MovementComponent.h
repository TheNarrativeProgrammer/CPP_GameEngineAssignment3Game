#pragma once
#include "Game/Public/Components/Component.h"
#include "Engine/Public/EngineTypes.h"

class MovementComponent : public Component
{
	friend class Actor;
public:
	void MoveActorUp();
	void MoveActorDown();
	void MoveActorLeft();
	void MoveActorRight();

protected:
	MovementComponent(std::weak_ptr<Actor> owner, exVector2& velocity);


public:
	MovementComponent() = delete;

	virtual bool CanAddComponent() const;

	//member varaibles
	exVector2 mVelocity;
	float mChangeToVelocityOnButtonPress = 0.03f;
};

