#include "Game/Public/Actors/Ship.h"

Ship::Ship(String shipName, exColor shipColor, exVector2 startingPos, exVector2 velocity) :
mShipName(shipName),
mShipColor(shipColor),
mShipStartingPosition(startingPos),
mShipInitialVelocity(velocity)
{
	
}

void Ship::BeginPlay()
{
	AddComponentOfType<TransformComponent>(mShipStartingPosition);
	AddComponentOfType<BoxRenderComponent>(200.0f, 50.0f, mShipColor);
	AddComponentOfType<CircleRenderComponent>(50.0f, mShipColor, exVector2(0.0f, -25.0f));
	std::tuple<std::shared_ptr<CircleColliderComponent>, bool, String> Result = AddComponentOfType<CircleColliderComponent>(100.0f, mShipInitialVelocity);
	std::shared_ptr<CircleColliderComponent> ColliderComp = std::get<0>(Result);

	if (ColliderComp) 
	{
		CollisionEventSignature delegate = std::bind(&Ship::OnShipCollided, this, std::placeholders::_1, std::placeholders::_2);
		ColliderComp->ListenForCollision(delegate);
	}
}

void Ship::OnShipCollided(std::weak_ptr<Actor> HitActor, const exVector2& HitPosition)
{
	if (std::shared_ptr<CircleRenderComponent> CircleRenderComp = FindComponentOfType<CircleRenderComponent>()) 
	{
		CircleRenderComp->SetColor(exColor({ 15,255,60,255 }));
	}
}
