#include "Game/Public/Components/BoxColliderComponent.h"
#include "Game/Public/Components/TransformComponent.h"
#include "Game/Public/Actors/Actor.h"

float BoxColliderComponent::GetWidth() const
{
    return mWidth;
}

float BoxColliderComponent::GetHeight() const
{
    return mHeight;
}

BoxColliderComponent::BoxColliderComponent(std::weak_ptr<Actor> owner, float width, float height, exVector2 velocity, bool isStatic, bool isGravityEnabled) :
    PhysicsComponent(owner, velocity, isStatic, isGravityEnabled)
    , mHeight(height)
    , mWidth(width)
{

}

bool BoxColliderComponent::CanAddComponent() const
{
    return true;
}

bool BoxColliderComponent::IsCollisionDetected(std::weak_ptr<PhysicsComponent> otherComponent)
{
    if (!otherComponent.expired()) 
    {
        std::shared_ptr<BoxColliderComponent> Self = std::dynamic_pointer_cast<BoxColliderComponent>(shared_from_this());

        return otherComponent.lock()->IsCollisionDetectedWithBox(Self);
    }
}

bool BoxColliderComponent::IsCollisionDetectedWithBox(std::weak_ptr<BoxColliderComponent> otherComponent)
{
    exVector2 selfCenterPos;
    exVector2 otherCenterPos;

    float selfWidth = mWidth;
    float selfHeight = mHeight;
    float otherWidth = otherComponent.lock()->mWidth;
    float otherHeight = otherComponent.lock()->mHeight;

    float selfX;
    float selfY;
    float otherX;
    float otherY;

    if (!mOwner.expired()) 
    {
        if (const std::shared_ptr<TransformComponent> TransformComp = mOwner.lock()->FindComponentOfType<TransformComponent>())
        {
            selfCenterPos = TransformComp->GetLocation();

            //converting the center pos to the top left corner
            selfX = selfCenterPos.x - (selfWidth / 2);
            selfY = selfCenterPos.y - (selfHeight / 2);
        }
    }

    if (!otherComponent.expired())
    {
        if (!otherComponent.lock()->mOwner.expired())
        {
            if (const std::shared_ptr<TransformComponent> TransformComp = otherComponent.lock()->mOwner.lock()->FindComponentOfType<TransformComponent>())
            {
                otherCenterPos = TransformComp->GetLocation();

                otherX = otherCenterPos.x - (otherWidth / 2);
                otherY = otherCenterPos.y - (otherHeight / 2);

                // check for collision.
                if (selfX + selfWidth >= otherX &&  // self right edge past other left
                    selfX <= otherX + otherWidth &&  // self left edge past other right
                    selfY + selfHeight >= otherY &&  // self bottom edge past other top
                    selfY <= otherY + otherHeight) // self top edge past other bottom
                {
                    return true;
                }  
            }
        }
    }

    return false;
}

bool BoxColliderComponent::IsCollisionDetectedWithCircle(std::weak_ptr<CircleColliderComponent> otherComponent)
{
    exVector2 boxCenterPos;
    exVector2 circleCenterPos;

    float selfWidth = mWidth;
    float selfHeight = mHeight;

    if (!mOwner.expired()) 
    {
        if (const std::shared_ptr<TransformComponent> TransformComp = mOwner.lock()->FindComponentOfType<TransformComponent>())
        {
            boxCenterPos = TransformComp->GetLocation();
        }
    }

    if (!otherComponent.expired())
    {
        if (!otherComponent.lock()->GetOwner().expired())
        {
            float circleRadius = otherComponent.lock()->GetRadius();

            if (const std::shared_ptr<TransformComponent> TransformComp = otherComponent.lock()->GetOwner().lock()->FindComponentOfType<TransformComponent>())
            {
                circleCenterPos = TransformComp->GetLocation();

                // Convert Box Center to Top-Left Corner
                float boxX = boxCenterPos.x - (selfWidth / 2);
                float boxY = boxCenterPos.y - (selfHeight / 2);

                // Find Closest Point on Box to Circle
                float closestX = std::max(boxX, std::min(circleCenterPos.x, boxX + selfWidth));
                float closestY = std::max(boxY, std::min(circleCenterPos.y, boxY + selfHeight));

                // Compute Distance Squared
                float distX = circleCenterPos.x - closestX;
                float distY = circleCenterPos.y - closestY;
                float distanceSquared = (distX * distX) + (distY * distY);

                // If distance squared is less than the squared radius, collision detected but currently does not 
                // know if the collision happened on what specific side of the box.
                return distanceSquared < (circleRadius * circleRadius);
            }
        }
    }

    return false;
}
