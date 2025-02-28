#include "Game/Public/Actors/Rock.h"


Rock::Rock(exColor rockColor, exVector2 startingPos, exVector2 velocity, float radius) :
    mRockColor(rockColor),
    mRockStartingPosition(startingPos),
    mRockInitialVelocity(velocity),
    mRockRadius(radius)
{
}

void Rock::BeginPlay()
{
    AddComponentOfType<TransformComponent>(mRockStartingPosition);
    AddComponentOfType<CircleColliderComponent>(mRockRadius, mRockInitialVelocity);
    AddComponentOfType<CircleRenderComponent>(mRockRadius, mRockColor);

    std::tuple<std::shared_ptr<CircleColliderComponent>, bool, String> Result = AddComponentOfType<CircleColliderComponent>(mRockRadius, mRockInitialVelocity);
    std::shared_ptr<CircleColliderComponent> ColliderComp = std::get<0>(Result);

    if (ColliderComp)
    {
        CollisionEventSignature delegate = std::bind(&Rock::OnRockCollided, this, std::placeholders::_1, std::placeholders::_2);
        ColliderComp->ListenForCollision(delegate);
    }
}

void Rock::OnRockCollided(std::weak_ptr<Actor> HitActor, const exVector2& HitPosition)
{
    //// Check if the collided actor is a Player
    //if (auto player = std::dynamic_pointer_cast<Player>(HitActor.lock()))
    //{
    //    this->Destroy(); // Destroy both the rock and the player
    //    player->Destroy(); // Destroy the player

    //    TriggerGameOver();
    //}
}