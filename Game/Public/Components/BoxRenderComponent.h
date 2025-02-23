#pragma once
#include "RenderComponent.h"


class BoxRenderComponent : public RenderComponent
{
	friend class Actor;

public:
	
	BoxRenderComponent() = delete;

protected:

	// width height, (top left bottom right) (center)
	BoxRenderComponent(std::weak_ptr<Actor> owner, float width, float height, exColor color = { 0, 255, 0, 255 }, exVector2 positionOffset = { 0.0f, 0.0f }, int layID = 1);

	virtual void Render(exEngineInterface* renderInterface) override;
	virtual bool CanAddComponent() const override;

private:

	float mHeight;
	float mWidth;
};

