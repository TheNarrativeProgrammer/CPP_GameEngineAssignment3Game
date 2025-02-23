#include "Game/Public/Components/Component.h"

Component::~Component()
{
}

Component::Component(std::weak_ptr<Actor> owner) : mOwner(owner)
{
}

void Component::InitializeComponent()
{
}

void Component::DeinitializeComponent()
{
}

void Component::TickComponent(float deltaSeconds)
{
}

bool Component::CanAddComponent() const
{
	return true;
}
