//
// * ENGINE-X
// * SAMPLE GAME
//
// + Game.h
// definition of MyGame, an implementation of exGameInterface
//

#include "Game/Public/GameInterface.h"
#include "Engine/Public/EngineTypes.h"
#include "Game/Public/GameCore/GameCore.h"
#include "Game/Public/StateMachine/StateMachine.h"
#include "Game/Public/Actors/Rock.h"
#include "Game/Public/Actors/RockSpawner.h"


#include <iomanip>
#include <sstream> //for std::fixed and std::setprecision

//-----------------------------------------------------------------
//-----------------------------------------------------------------
class Actor;
class Ship;


class MyGame : public exGameInterface
{
public:

								MyGame();
	virtual						~MyGame();

	virtual void				Initialize( exEngineInterface* pEngine );

	virtual const char*			GetWindowName() const;
	virtual void				GetClearColor( exColor& color ) const;

	virtual void				OnEvent( SDL_Event* pEvent );
	virtual void				OnEventsConsumed();

	virtual void				Run( float fDeltaT );

	virtual void				UpdateTimer(float fDeltaT);

	float						mTimeElasped;

private:

	exEngineInterface*			mEngine;

	int							mFontID;

	bool						mUp;
	bool						mDown;

	exVector2					mTextPosition;
	exVector2					mGameOverPosition;

	std::shared_ptr<Actor>		mRightBoarderGameBoard;
	std::shared_ptr<Actor>		mLeftBoarderGameBoard;
	std::shared_ptr<Actor>		mTopBoarderGameBoard;
	std::shared_ptr<Actor>		mBottomBoarderGameBoard;
	std::shared_ptr<Actor>		Character2;
	std::shared_ptr<Ship>		mShip;

	std::shared_ptr<StateMachine<Actor>> mStateMachine;

	std::shared_ptr<RockSpawner> mRockSpawner;

	
	
	

};
