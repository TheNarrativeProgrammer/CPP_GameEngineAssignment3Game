#include "Game/Public/Singletons/InputState.h"

std::unique_ptr<InputState> InputState::sInputStateInstance = nullptr;												//initialize ptr and set to null. GetInstance needs sInputStateInstance to exist in order to check if it's null.

InputState::~InputState()
{
}




InputState::InputState()
{
	mUp		= ((unsigned int) DirectionKeys::UP);
	mDown	= ((unsigned int) DirectionKeys::DOWN);
	mLeft	= ((unsigned int) DirectionKeys::LEFT);
	mRight	= ((unsigned int) DirectionKeys::RIGHT);
}


bool InputState::IsUp()
{
	return mUp;
}

bool InputState::IsDown()
{
	return mDown;
}

bool InputState::IsLeft()
{
	return mLeft;
}

bool InputState::IsRight()
{
	return mRight;
}



