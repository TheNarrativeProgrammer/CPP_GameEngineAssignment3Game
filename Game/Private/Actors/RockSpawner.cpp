#include "Game/Public/Actors/RockSpawner.h"
#include "Game/Public/Actors/Rock.h"
#include <random>



RockSpawner::RockSpawner(String actorName, exColor actorColor, exVector2 startingPos, exVector2 velocity, float spawnInterval, float screenWidth, float screenHeight)
    : mSpawnInterval(spawnInterval)
    , mScreenWidth(screenWidth)
    , mScreenHeight(screenHeight)
    , mSpawnTimer(0.0f)
    , mRockSpawnerName(actorName)
    , mRockSpawnerStartingPosition(startingPos)
    , mRockSpawnerColor(actorColor)
{
}

void RockSpawner::BeginPlay()
{
    Actor::BeginPlay();
    mSpawnTimer = 0.0f;
}

void RockSpawner::TickSpawnRock(float deltaSeconds)
{
    //Actor::Tick(deltaSeconds);

    mSpawnTimer += deltaSeconds;
    //SpawnRock();
    if (mSpawnTimer >= mSpawnInterval)
    {
        //SpawnRock();
        mSpawnTimer = 0.0f;
    }
}

std::shared_ptr<Rock> RockSpawner::SpawnRock()
{
    // Use static random generator for consistent randomness
    //static std::random_device rd;
    //static std::mt19937 gen(rd());

    // Random position within screen boundaries
    //std::uniform_real_distribution<float> xDist(0.0f, mScreenWidth);
    //std::uniform_real_distribution<float> yDist(0.0f, mScreenHeight);

    //float xPos = xDist(gen);
    float xPos = 100;
    //float yPos = yDist(gen);
    float yPos = 100;

    // Fixed velocity
    float velocityX = 0.0f;
    float velocityY = -0.1f;    //moving down

    // Fixed radius
    float rockRadius = 5.0f;

    // Brown color 
    exColor rockColor = {
        static_cast<unsigned char>(165),
        static_cast<unsigned char>(42),
        static_cast<unsigned char>(42),
        255
    };

    // Create and initialize the rock
   std::shared_ptr<Rock> newRock = std::make_shared<Rock>(rockColor, exVector2(xPos, yPos), exVector2(velocityX, velocityY), rockRadius);
   newRock->BeginPlay();
   return newRock;
    

}
