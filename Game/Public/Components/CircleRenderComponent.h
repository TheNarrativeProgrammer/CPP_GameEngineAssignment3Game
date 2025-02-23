#pragma once
#include "RenderComponent.h"


class CircleRenderComponent : public RenderComponent
{
	friend class Actor;

public:

	CircleRenderComponent() = delete;

protected:

	CircleRenderComponent(std::weak_ptr<Actor> owner, float radius, exColor color = { 255, 0, 0, 255 }, exVector2 positionOffset = { 0.0f, 0.0f }, int layerID = 1);

	virtual void Render(exEngineInterface* renderInterface) override;
	virtual bool CanAddComponent() const override;
private:

	float mRadius; // write getter and setter.

};

