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

	std::shared_ptr<Actor>		RightBoarderGameBoard;
	std::shared_ptr<Actor>		LeftBoarderGameBoard;
	std::shared_ptr<Actor>		TopBoarderGameBoard;
	std::shared_ptr<Actor>		BottomBoarderGameBoard;
	std::shared_ptr<Actor>		Character2;
	std::shared_ptr<Ship>		mShip;

	std::shared_ptr<StateMachine<Actor>> mStateMachine;

	

	

};
