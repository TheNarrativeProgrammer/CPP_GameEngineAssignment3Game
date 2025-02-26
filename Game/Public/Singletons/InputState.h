#pragma once
#include "Game/Public/GameCore/GameCore.h"

enum class DirectionKeys : unsigned int
{
	DEFAULT		= 1,
	UP			= (DEFAULT << 0),
	DOWN		= (DEFAULT << 1),
	LEFT		= (DEFAULT << 2),
	RIGHT		= (DEFAULT << 3),
};

class InputState
{
	friend class InputManager;

public:
	//DESTUCTOR
	~InputState();

	//GET INSTANCE																		//check if instance exist. If no instance exist, reset the unique_ptr and call the default constructor. 
	static InputState& GetInstance()
	{
		if (!sInputStateInstance)
		{
			sInputStateInstance.reset(new InputState());
		}
		return *sInputStateInstance;													//dereference and return InputState
	}


protected:
	unsigned int mUp		: 1;
	unsigned int mDown		: 1;
	unsigned int mLeft		: 1;
	unsigned int mRight		: 1;

	bool IsUp();
	bool IsDown();
	bool IsLeft();
	bool IsRight();


private:
	//CONSTRUCTORS	
	InputState();																																											//default constuctor
																							//delete the copy construtor and copy assignment operator to prevent copying of singleton
	InputState(const InputState& otherInputState) = delete;																																	//copy constructor
	InputState& operator=(const InputState& otherInputState) = delete;																														//copy assignment operator

	//STATIC INSTANCE
	static std::unique_ptr<InputState> sInputStateInstance;
};

