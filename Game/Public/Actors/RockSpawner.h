#pragma once

#include "Actor.h"
#include <memory>
#include <random>
#include "Game/Public/GameCore/GameCore.h"
#include "Engine/Public/EngineTypes.h"
#include "Game/Public/Actors/Rock.h"

class RockSpawner : public Actor
{
public:
    RockSpawner() = delete;
    RockSpawner(String actorName, float spawnInterval, float screenWidth, float screenHeight);

    virtual void BeginPlay() override;
    void TickSpawnRock(float deltaSeconds);
    virtual void Tick(float deltaSeconds) override;

    // Spawn a rock at a random screen position with random velocity
    //std::shared_ptr<Rock> SpawnRock();

    void SpawnRock();

protected:

    float mSpawnTimer;
    float mSpawnInterval;

    const float mScreenWidth;
    const float mScreenHeight;

    String mRockSpawnerName;

    // List to store rocks
    std::vector<std::shared_ptr<Rock>> mRocks;

};
