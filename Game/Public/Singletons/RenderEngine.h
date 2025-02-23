#pragma once
#include "Game/Public/GameCore/GameCore.h"
//#include "Engine/Public/EngineTypes.h"

#define RENDER_ENGINE RenderEngine::GetInstance()
class RenderComponent;
class exEngineInterface;

class RenderEngine
{
	
public:

	static RenderEngine& GetInstance() 
	{
		if (!sRenderEngineInstance) 
		{			
			// reset is taking the new memory block you create with renderengine() and reassigns it to the unique ptr. 
			sRenderEngineInstance.reset(new RenderEngine()); 
		}
		return *sRenderEngineInstance;
	}
	
	~RenderEngine();

	void Render(exEngineInterface* engineInterface);

#pragma region Listeners

	void AddRenderComponent(std::weak_ptr<RenderComponent> componentToAdd);
	void ClearInvalidRenderComponents();
#pragma endregion

private:

	RenderEngine();

	// delete the copy constructor and the operator overload to prevent copying of a singleton class
	RenderEngine(const RenderEngine& otherEngine) = delete;
	RenderEngine& operator=(const RenderEngine& otherEngine) = delete; 

	std::list<std::weak_ptr<RenderComponent>> mRenderComponents;

	static std::unique_ptr<RenderEngine> sRenderEngineInstance;
}; 

