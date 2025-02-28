#include "Game/Public/Actors/Actor.h"

Actor::Actor()
{
	mCanEverTick = false;
}

Actor::~Actor()
{
}

void Actor::BeginPlay()
{
}

void Actor::SetCanEverTick(bool inCanEverTick)
{
	mCanEverTick = inCanEverTick;
}

void Actor::EndPlay()
{
}

void Actor::Tick(float deltaSeconds)
{
}
