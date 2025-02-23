#pragma once
#include "Game/Public/GameCore/GameCore.h"

class Actor;

class Component
{
	friend Actor;

public:
	Component() = delete;
	virtual ~Component();

	std::weak_ptr<Actor> GetOwner() const { return mOwner; }

protected:

	Component(std::weak_ptr<Actor> owner);
	virtual void InitializeComponent();
	virtual void DeinitializeComponent();
	virtual void TickComponent(float deltaSeconds);
	virtual bool CanAddComponent() const;


	std::weak_ptr<Actor> mOwner;
};

using ComponentList = std::list<std::shared_ptr<Component>>;

