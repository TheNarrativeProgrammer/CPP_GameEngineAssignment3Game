#pragma once
#include "Game/Public/Singletons/InputManager.h"
#include <conio.h>
#include <chrono>
#include <thread>
#include <Windows.h>

#include <Engine/Public/SDL.h>

std::unique_ptr<InputManager>InputManager::sInputManagerInstance = nullptr;

InputManager::~InputManager()
{
}

InputManager::InputManager() : mInputState(InputState::GetInstance())
{
}

void InputManager::Update()
{
	ChangeButtonPress();
	mInputState.mUp = IsButtonPressed('w');
	mInputState.mDown = IsButtonPressed('s');
	mInputState.mLeft = IsButtonPressed('a');
	mInputState.mRight = IsButtonPressed('d');
	//std::this_thread::sleep_for(std::chrono::milliseconds(3000));
}

bool InputManager::IsButtonPressed(char inWASD)
{
	static bool isKeyUp = true;

	if (mLastKeyPressed == inWASD)
	{
		if (isKeyUp == true)
		{
			isKeyUp = false;
			return true;
		}
	}
	else
	{
		isKeyUp = true;
	}
	return false;
}

void InputManager::ChangeButtonPress()
{

	bool key = _kbhit();
	char pressed = _getch();

	int numberOfKeysInKeyBoardState = 0;
	const Uint8* keyBoardState = SDL_GetKeyboardState(&numberOfKeysInKeyBoardState);
	
	if (keyBoardState[SDL_SCANCODE_W] == 1)
	{
		mLastKeyPressed = 'w';
	}
	if (keyBoardState[SDL_SCANCODE_S] == 1)
	{
		mLastKeyPressed = 's';
	}
	if (keyBoardState[SDL_SCANCODE_A] == 1)
	{
		mLastKeyPressed = 'a';
	}
	if (keyBoardState[SDL_SCANCODE_D] == 1)
	{
		mLastKeyPressed = 'd';
	}
		
}

void InputManager::MoveShip(Ship& inShip)
{
	if (mInputState.IsUp())
	{
		inShip.FindComponentOfType<MovementComponent>()->MoveActorUp();
	}
	if (mInputState.IsDown())
	{
		inShip.FindComponentOfType<MovementComponent>()->MoveActorDown();
	}
	if (mInputState.IsLeft())
	{
		inShip.FindComponentOfType<MovementComponent>()->MoveActorLeft();
	}
	if (mInputState.IsRight())
	{
		inShip.FindComponentOfType<MovementComponent>()->MoveActorRight();
	}
}


