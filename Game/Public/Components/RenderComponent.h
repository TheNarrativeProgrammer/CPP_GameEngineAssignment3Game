#pragma once
#include "Component.h"
#include "Engine/Public/EngineTypes.h"


class exEngineInterface;

// enabled shared from this is a standard library interface that lets us create weak ptr and shared ptrs from our own reference
class RenderComponent : public Component, public std::enable_shared_from_this<RenderComponent>
{
	friend class Actor;

public:

	RenderComponent() = delete;
	virtual void Render(exEngineInterface* renderInterface) = 0;
	void SetColor(const exColor newColor);
	exColor GetColor() const;
protected:
	
	RenderComponent(std::weak_ptr<Actor> owner, exColor color = { 125,125,125,255 }, exVector2 renderOffset = {0.0f, 0.0f}, int layerID = 0); // RGBA and = means optional param

	// render interface could be a weak ptr ora  shared ptr if you want ownership for your game
	virtual bool CanAddComponent() const override;
	virtual void InitializeComponent() override;

	exColor mColor;
	exVector2 mRenderOffset;
	int mLayerId;
};

