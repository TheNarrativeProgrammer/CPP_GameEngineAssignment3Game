#include "Game/Public/Components/PhysicsComponent.h"
#include "Game/Public/Actors/Actor.h"
#include "Game/Public/Components/TransformComponent.h"
#include "Game/Public/Singletons/PhysicsEngine.h"

void PhysicsComponent::DoPhysics()
{
    if (!mOwner.expired()) 
    {
        if (mIsStatic) return;

        if (const std::shared_ptr<TransformComponent> TransformComp = mOwner.lock()->FindComponentOfType<TransformComponent>()) 
        {
            exVector2 newPosition = TransformComp->GetLocation() + mVelocity;
            // add extra logic for gravity if your game calls for it. 
            TransformComp->SetLocation(newPosition);
        }
    }
}

PhysicsComponent::PhysicsComponent(std::weak_ptr<Actor> owner, exVector2 velocity, bool isStatic, bool isGravityEnabled) 
    : Component(owner), mVelocity(velocity), mIsStatic(isStatic), mIsGravity(isGravityEnabled)
{
    
}

void PhysicsComponent::InitializeComponent()
{
    PHYSICS_ENGINE.AddPhysicsComponent(weak_from_this());
}

//you should not be able to add a default physics component, you should only be able to use it through inheritance.
bool PhysicsComponent::CanAddComponent() const
{
    return false;
}

void PhysicsComponent::ListenForCollision(CollisionEventSignature& delegateToAdd)
{
    mCollisionEvents.emplace_back(delegateToAdd);
}

void PhysicsComponent::StopListeningForCollision(CollisionEventSignature& delegateToRemove)
{
    mCollisionEvents.erase(std::remove_if(mCollisionEvents.begin(), mCollisionEvents.end(),
        [delegateToRemove](const CollisionEventSignature& collisionEventIterator)->bool
        {
            return *delegateToRemove.target<void(*)(std::weak_ptr<Actor>, const exVector2&)>() 
                == *collisionEventIterator.target<void(*)(std::weak_ptr<Actor>, const exVector2&)>();
        }), mCollisionEvents.end());
}

bool PhysicsComponent::DoBothHaveCircleCollider(const std::weak_ptr<Actor> firstActor, const std::weak_ptr<Actor> otherActor)
{
    if (firstActor.lock()->FindComponentOfType<CircleColliderComponent>() != nullptr 
        && otherActor.lock()->FindComponentOfType<CircleColliderComponent>() != nullptr
        && !firstActor.expired() && !otherActor.expired())
    {
        return true;
    }
    return false;
}

void PhysicsComponent::BroadcastCollisionEvents(std::weak_ptr<Actor>& otherActor, const exVector2 hitLocation)
{ // this will say in the phys comp "hey i collided with this thing" and whoever is listening will get the events back. 
    for (CollisionEventSignature& event : mCollisionEvents) 
    {
        event(otherActor, hitLocation);
    }
}

//bool PhysicsComponent::IsCollisionDetected(std::weak_ptr<PhysicsComponent> otherComponent) const
//{
//    return false;
//}

void PhysicsComponent::CollisionResolution()
{
    if (mIsStatic) return;
    SetVelocity(mVelocity * -1.0f);
}

void PhysicsComponent::CircleCollisionResolution(std::weak_ptr<Actor>& firstActor, std::weak_ptr<Actor>& secondActor)
{
    exVector2 selfCenterPos = firstActor.lock()->FindComponentOfType<TransformComponent>()->GetLocation();
    exVector2 otherCenterPos = secondActor.lock()->FindComponentOfType<TransformComponent>()->GetLocation();

    exVector2 otherVelocity = secondActor.lock()->FindComponentOfType<PhysicsComponent>()->GetVelocity();


    exVector2 normal = (otherCenterPos - selfCenterPos).Normalize();

    float v1n = mVelocity.Dot(normal);
    float v2n = otherVelocity.Dot(normal);

    float v1n_final = v2n;
    float v2n_final = v1n;

    exVector2 tangent = exVector2{ -normal.y, normal.x };

    float v1t = mVelocity.Dot(tangent);
    float v2t = otherVelocity.Dot(tangent);


    mVelocity = (normal * v1n_final);
    otherVelocity = (normal * v2n_final);
    firstActor.lock()->FindComponentOfType<PhysicsComponent>()->SetVelocity(mVelocity);
    secondActor.lock()->FindComponentOfType<PhysicsComponent>()->SetVelocity(otherVelocity);
}

void PhysicsComponent::SetVelocity(const exVector2 inVelocity)
{
    mVelocity = inVelocity;
}

exVector2 PhysicsComponent::GetVelocity() const
{
    return mVelocity;
}
