#include "Game/Public/Components/TransformComponent.h"
#include "Game/Public/Actors/Actor.h"

TransformComponent::TransformComponent(std::weak_ptr<Actor> owner, exVector2 location) : Component(owner), mLocation(location)
{
}

exVector2 TransformComponent::GetLocation() const
{
	return mLocation;
}

void TransformComponent::SetLocation(const exVector2 inValue)
{
	mLocation = inValue;
}

bool TransformComponent::CanAddComponent() const
{
	if (!mOwner.expired()) 
	{
		return !mOwner.lock()->FindComponentOfType<TransformComponent>();
	}
	return true;
}
