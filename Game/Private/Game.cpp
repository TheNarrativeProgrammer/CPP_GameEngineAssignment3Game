//
// * ENGINE-X
// * SAMPLE GAME
//
// + Game.cpp
// implementation of MyGame, an implementation of exGameInterface
//

#include "Game/Public/Game.h"

#include "Engine/Public/EngineInterface.h"
#include "Engine/Public/SDL.h"

#include "Game/Public/Actors/Actor.h"
#include "Game/Public/Singletons/RenderEngine.h"

#include "Game/Public/Singletons/PhysicsEngine.h"
#include "Game/Public/Actors/Ship.h"
//-----------------------------------------------------------------
//-----------------------------------------------------------------

const char* gWindowName = "Sample EngineX Game";

//-----------------------------------------------------------------
//-----------------------------------------------------------------

MyGame::MyGame()
	: mEngine( nullptr )
	, mFontID( -1 )
	, mUp( false )
	, mDown( false )
{
}

//-----------------------------------------------------------------
//-----------------------------------------------------------------

MyGame::~MyGame()
{
}

//-----------------------------------------------------------------
//-----------------------------------------------------------------

void MyGame::Initialize( exEngineInterface* pEngine )
{
	mEngine = pEngine;

	mFontID = mEngine->LoadFont( "Resources/Jersey.ttf", 32 );

	mTextPosition.x = 50.0f;
	mTextPosition.y = 50.0f;

	Character1 = std::make_shared<Actor>();
	Character1->AddComponentOfType<TransformComponent>(exVector2(450.0f, 300.0f));
	Character1->AddComponentOfType<CircleRenderComponent>(100.0f);
	Character1->AddComponentOfType<BoxColliderComponent>(100.0f, 100.0f, exVector2({-1.0f, 0.0f})); 
		// box collider will collide with circle onship

	Character2 = std::make_shared<Actor>();
	Character2->AddComponentOfType<TransformComponent>(exVector2(25.0f, 25.0f)); // this effects the size of the box.
	Character2->AddComponentOfType<BoxRenderComponent>(250.0f, 250.0f, exColor({0, 255, 125, 255}), exVector2(0.0f, 0.0f), 1);
	Character2->AddComponentOfType<CircleColliderComponent>(50.0f, exVector2({ 0.0f, 0.0f }), true);

	mShip = std::make_shared<Ship>("Pirate Ship", exColor({255,100,100,255}), exVector2(100.0f, 300.0f), exVector2(0.4f, 0.0f));
	mShip->BeginPlay();

	//mStateMachine = std::make_shared<StateMachine<Actor>>();
	//mStateMachine->AddState("GamePlay", std::make_shared<Gameplay>()); // needs to match the state name exactly
	//mStateMachine->AddState("MainMenu", std::make_shared<MainMenu>()); // needs to match the state name exactly
	//mStateMachine->AddState("EndGame", std::make_shared<EndGame>()); // needs to match the state name exactly

	//mStateMachine->SetState("MainMenu", nullptr);
}


//-----------------------------------------------------------------
//-----------------------------------------------------------------

const char* MyGame::GetWindowName() const
{
	return gWindowName;
}

//-----------------------------------------------------------------
//-----------------------------------------------------------------

void MyGame::GetClearColor( exColor& color ) const
{
	color.mColor[0] = 128;
	color.mColor[1] = 128;
	color.mColor[2] = 128;
}

//-----------------------------------------------------------------
//-----------------------------------------------------------------

void MyGame::OnEvent( SDL_Event* pEvent )
{
}

//-----------------------------------------------------------------
//-----------------------------------------------------------------

void MyGame::OnEventsConsumed()
{
	int nKeys = 0;
	const Uint8 *pState = SDL_GetKeyboardState( &nKeys );

	mUp = pState[SDL_SCANCODE_UP];
	mDown = pState[SDL_SCANCODE_DOWN];
}

//-----------------------------------------------------------------
//-----------------------------------------------------------------

void MyGame::Run( float fDeltaT )
{
	if ( mUp )
	{
		mTextPosition.y -= 40.0f * fDeltaT;
	}
	else if ( mDown )
	{
		mTextPosition.y += 40.0f * fDeltaT;
	}

	//if (Character) ---- NOT NEEDED BECAUSE OF RENDER_ENGINE.
	//{
	//	if (std::shared_ptr<TransformComponent> TransformComp = Character->FindComponentOfType<TransformComponent>())
	//	{
	//		//TransformComp->SetLocation(TransformComp->GetLocation() += mTextPosition);
	//	}

	//	for (std::shared_ptr<RenderComponent> RenderCompIter : Character->FindAllComponentOfType<RenderComponent>()) 
	//	{
	//		RenderCompIter->Render(mEngine);
	//	}
	//}

	exVector2 p1, p2;
	exColor c;
	float r;

	c.mColor[0] = 25;
	c.mColor[1] = 255;
	c.mColor[2] = 0;
	c.mColor[3] = 255;

	p1.x = 175.0f;
	p1.y = 175.0f;

	r = 25.0f;

	mEngine->DrawLineCircle( p1, r, c, 0 );

	p1.x = 100.0f;
	p1.y = 100.0f;

	p2.x = 200.0f;
	p2.y = 200.0f;

	c.mColor[0] = 255;
	c.mColor[1] = 0;
	c.mColor[2] = 0;

	mEngine->DrawBox( p1, p2, c, 1 );

	p1.x = 400.0f;
	p1.y = 400.0f;

	p2.x = 500.0f;
	p2.y = 500.0f;

	mEngine->DrawLineBox( p1, p2, c, 1 );

	p1.x = 400.0f;
	p1.y = 400.0f;

	c.mColor[0] = 0;
	c.mColor[1] = 0;
	c.mColor[2] = 0;

	mEngine->DrawCircle( p1, r, c, 2 );

	mEngine->DrawText( mFontID, mTextPosition, "Yung Hitro", c, 0 );

	//mStateMachine->Update(nullptr);

	RENDER_ENGINE.Render(mEngine);
	PHYSICS_ENGINE.PhysicsUpdate(fDeltaT);
}
