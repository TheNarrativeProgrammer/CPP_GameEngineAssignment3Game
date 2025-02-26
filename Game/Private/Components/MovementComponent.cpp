#include "Game/Public/Components/MovementComponent.h"
#include "Game/Public/Actors/Actor.h"
#include "Game/Public/Components/TransformComponent.h"






void MovementComponent::MoveActorUp()
{
	if (const std::shared_ptr<PhysicsComponent> physicsComp = mOwner.lock()->FindComponentOfType<PhysicsComponent>())
	{
		exVector2 newVecolicty = physicsComp->GetVelocity();
		newVecolicty.y -= mChangeToVelocityOnButtonPress;
		physicsComp->SetVelocity(newVecolicty);
	}
	//mVelocity.y += mChangeToVelocityOnButtonPress;
}

void MovementComponent::MoveActorDown()
{
	if (const std::shared_ptr<PhysicsComponent> physicsComp = mOwner.lock()->FindComponentOfType<PhysicsComponent>())
	{
		exVector2 newVecolicty = physicsComp->GetVelocity();
		newVecolicty.y += mChangeToVelocityOnButtonPress;
		physicsComp->SetVelocity(newVecolicty);
	}
}

void MovementComponent::MoveActorLeft()
{
	if (const std::shared_ptr<PhysicsComponent> physicsComp = mOwner.lock()->FindComponentOfType<PhysicsComponent>())
	{
		exVector2 newVecolicty = physicsComp->GetVelocity();
		newVecolicty.x -= mChangeToVelocityOnButtonPress;
		physicsComp->SetVelocity(newVecolicty);
	}
}

void MovementComponent::MoveActorRight()
{
	if (const std::shared_ptr<PhysicsComponent> physicsComp = mOwner.lock()->FindComponentOfType<PhysicsComponent>())
	{
		exVector2 newVecolicty = physicsComp->GetVelocity();
		newVecolicty.x += mChangeToVelocityOnButtonPress;
		physicsComp->SetVelocity(newVecolicty);
	}
}

MovementComponent::MovementComponent(std::weak_ptr<Actor> owner, exVector2& velocity) : Component(owner), mVelocity(velocity)
{
}

bool MovementComponent::CanAddComponent() const
{
	if (!mOwner.expired())
	{
		return !mOwner.lock()->FindComponentOfType<MovementComponent>();
	}
	return true;
}
