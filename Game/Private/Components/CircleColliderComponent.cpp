#include "Game/Public/Components/CircleColliderComponent.h"
#include "Game/Public/Components/TransformComponent.h"
#include "Game/Public/Actors/Actor.h"

float CircleColliderComponent::GetRadius() const
{
	return mRadius;
}

CircleColliderComponent::CircleColliderComponent(std::weak_ptr<Actor> owner, float radius, exVector2 velocity, bool isStatic, bool isGravityEnabled) :
	PhysicsComponent(owner, velocity, isStatic, isGravityEnabled) 
	, mRadius(radius)
{

}

bool CircleColliderComponent::CanAddComponent() const
{
	return true;
}

bool CircleColliderComponent::IsCollisionDetected(std::weak_ptr<PhysicsComponent> otherComponent) 
{
	if (!otherComponent.expired()) 
	{
		std::shared_ptr<CircleColliderComponent> Self = std::dynamic_pointer_cast<CircleColliderComponent>(shared_from_this());

		return otherComponent.lock()->IsCollisionDetectedWithCircle(Self);
	}
	return false;
}

bool CircleColliderComponent::IsCollisionDetectedWithCircle(std::weak_ptr<CircleColliderComponent> otherComponent)
{

	exVector2 selfCenterPos;
	exVector2 otherCenterPos;
	
	if (!mOwner.expired())
	{
		if (const std::shared_ptr<TransformComponent> TransformComp = mOwner.lock()->FindComponentOfType<TransformComponent>()) 
		{
			selfCenterPos = TransformComp->GetLocation();
		}
	}

	if (!otherComponent.expired())
	{
		if (!otherComponent.lock()->mOwner.expired()) 
		{
			if (const std::shared_ptr<TransformComponent> TransformComp = otherComponent.lock()->mOwner.lock()->FindComponentOfType<TransformComponent>())
			{				
				otherCenterPos = TransformComp->GetLocation();

				exVector2 Length = selfCenterPos - otherCenterPos;
				float DistanceSquared = (Length.x * Length.x) + (Length.y * Length.y);
				float RadiusSum = mRadius + otherComponent.lock()->mRadius;
				return DistanceSquared < (RadiusSum * RadiusSum);
			}
		}		
	}

	return false;
}

bool CircleColliderComponent::IsCollisionDetectedWithBox(std::weak_ptr<BoxColliderComponent> otherComponent)
{
	exVector2 boxCenterPos;
	exVector2 circleCenterPos;

	float boxWidth, boxHeight;

	if (!mOwner.expired())
	{
		if (const std::shared_ptr<TransformComponent> TransformComp = mOwner.lock()->FindComponentOfType<TransformComponent>())
		{
			circleCenterPos = TransformComp->GetLocation();
		}
	}

	if (!otherComponent.expired())
	{
		if (!otherComponent.lock()->GetOwner().expired())
		{
			boxWidth = otherComponent.lock()->GetWidth();
			boxHeight = otherComponent.lock()->GetHeight();

			if (const std::shared_ptr<TransformComponent> TransformComp = otherComponent.lock()->GetOwner().lock()->FindComponentOfType<TransformComponent>())
			{
				boxCenterPos = TransformComp->GetLocation();

				float circleRadius = GetRadius();

				// Convert Box Center to Top-Left Corner
				float boxX = boxCenterPos.x - (boxWidth / 2);
				float boxY = boxCenterPos.y - (boxHeight / 2);

				// Find Closest Point on Box to Circle
				float closestX = std::max(boxX, std::min(circleCenterPos.x, boxX + boxWidth));
				float closestY = std::max(boxY, std::min(circleCenterPos.y, boxY + boxHeight));

				// Compute Distance Squared
				float distX = circleCenterPos.x - closestX;
				float distY = circleCenterPos.y - closestY;
				float distanceSquared = (distX * distX) + (distY * distY);

				// Collision check
				return distanceSquared < (circleRadius * circleRadius);
			}
		}
	}

	return false;
}
