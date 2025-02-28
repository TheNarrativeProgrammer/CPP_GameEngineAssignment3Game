#pragma once

#include "Actor.h"
#include <memory>
#include <random>
#include "Game/Public/GameCore/GameCore.h"
#include "Engine/Public/EngineTypes.h"
#include "Game/Public/Actors/Rock.h"

class RockSpawner : public Actor, std::enable_shared_from_this<RockSpawner>
{
public:
    RockSpawner() = delete;
    RockSpawner(String actorName, exColor actorColor, exVector2 startingPos, exVector2 velocity, float spawnInterval, float screenWidth, float screenHeight);

    virtual void BeginPlay() override;
    void TickSpawnRock(float deltaSeconds);

    // Spawn a rock at a random screen position with random velocity
    std::shared_ptr<Rock> SpawnRock();

private:

    float mSpawnTimer;
    float mSpawnInterval;

    const float mScreenWidth;
    const float mScreenHeight;

    String mRockSpawnerName;
    exColor mRockSpawnerColor;
    exVector2 mRockSpawnerStartingPosition;

};
