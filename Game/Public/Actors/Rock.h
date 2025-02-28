#pragma once
#include "Actor.h"
#include "Game/Public/GameCore/GameCore.h"
#include "Engine/Public/EngineTypes.h"
#include <memory>
class Rock : public Actor, std::enable_shared_from_this<Rock>
{
public:
    Rock() = delete;
    Rock(exColor rockColor, exVector2 startingPos, exVector2 velocity, float radius);

    virtual void BeginPlay() override;
    void OnRockCollided(std::weak_ptr<Actor> HitActor, const exVector2& HitPosition);

private:
    exColor mRockColor;
    exVector2 mRockStartingPosition;
    exVector2 mRockInitialVelocity;
    float mRockRadius;
};
