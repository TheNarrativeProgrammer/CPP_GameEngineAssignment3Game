#pragma once
#include "Game/Public/GameCore/GameCore.h"
#include "Game/Public/Singletons/InputState.h"
#include "Game/Public/Actors/Ship.h"


class InputManager
{
public:
	~InputManager();

	//GET INSTANCE
	static InputManager& GetInstance()
	{
		if (!sInputManagerInstance)
		{
			sInputManagerInstance.reset(new InputManager());
		}
		return *sInputManagerInstance;
	}

	//FUNCTIONS
	void Update();
	bool IsButtonPressed(char inWASD);
	void ChangeButtonPress();
	void MoveShip(Ship& inShip);


private:
	//CONSTUCTORS
	InputManager();																																				//deflault constructor
																		//delete the copy construtor and copy assignment operator to prevent copying of singleton

	InputManager(const InputManager& otherInputManager) = delete;																								//copy constructor			
	InputManager& operator=(const InputManager& otherInputManager) = delete;																					//copy assig op

	//INSTANCE
	static std::unique_ptr<InputManager> sInputManagerInstance;			//self instance

	InputState& mInputState;											//Reference to InputState singleton

	//MEMBER VARIABLES
	char mLastKeyPressed;
};

