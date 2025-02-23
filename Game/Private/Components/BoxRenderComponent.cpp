#include "Game/Public/Components/BoxRenderComponent.h"
#include "Engine/Public/EngineInterface.h"
#include "Game/Public/Components/TransformComponent.h"
#include "Game/Public/Actors/Actor.h"




BoxRenderComponent::BoxRenderComponent(std::weak_ptr<Actor> owner, float width, float height, exColor color, exVector2 positionOffset, int layerID) :
	RenderComponent(owner, color, positionOffset, layerID),
	mWidth(width),
	mHeight(height)
{
}

void BoxRenderComponent::Render(exEngineInterface* renderInterface)
{
	if (renderInterface) 
	{
		exVector2 CenterPos = { 0.0f, 0.0f }; // fix this
		exVector2 TopLeft;
		exVector2 BottomRight;

		if (!mOwner.expired())
		{
			if (std::shared_ptr<TransformComponent> OwningTransformComp = mOwner.lock()->FindComponentOfType<TransformComponent>())
			{
				CenterPos = OwningTransformComp->GetLocation();
			}
		}
		CenterPos += mRenderOffset;
		TopLeft = { CenterPos.x -(0.5f * mWidth),CenterPos.y -(0.5f * mHeight)};
		BottomRight = { CenterPos.x + (0.5f * mWidth), CenterPos.y + (0.5f * mHeight) };

		renderInterface->DrawBox(TopLeft, BottomRight, mColor, mLayerId);
		
			
		renderInterface->DrawLineBox(TopLeft, BottomRight, {0,0,255,255}, mLayerId - 1);	
		
	}
}

bool BoxRenderComponent::CanAddComponent() const
{
	return true;
}