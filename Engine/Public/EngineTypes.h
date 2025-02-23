//
// * ENGINE-X
//
// + Types.h
// representations of: 2D vector with floats, 2D vector with integers and RBGA color as four bytes
//

#pragma once

//-----------------------------------------------------------------
//-----------------------------------------------------------------

struct exVector2
{
	float x, y;

	exVector2 operator+=(const exVector2& OtherVector) 
	{
		x += OtherVector.x;
		y += OtherVector.y;
		return *this;
	}

	exVector2 operator-=(const exVector2& OtherVector)
	{
		x -= OtherVector.x;
		y -= OtherVector.y;
		return *this;
	}

	exVector2 operator+(const exVector2& OtherVector)
	{
		exVector2 Result;
		Result.x = x + OtherVector.x;
		Result.y = y + OtherVector.y;
		return Result;
	}

	exVector2 operator-(const exVector2& OtherVector)
	{
		exVector2 Result;
		Result.x = x - OtherVector.x;
		Result.y = y - OtherVector.y;
		return Result;
	}

	exVector2 operator*(const float& OtherFloat)
	{
		exVector2 Result;
		Result.x = x * OtherFloat;
		Result.y = y * OtherFloat;
		return Result;
	}
	// TODO MULTIPLY BY DECIMAL, / IS EXPENSIVE
	/*exVector2 operator/(const float& OtherFloat)
	{
		exVector2 Result;
		Result.x = x / OtherFloat;
		Result.y = y / OtherFloat;
		return Result;
	}*/
};

//-----------------------------------------------------------------
//-----------------------------------------------------------------

struct exIntegerVector2
{
	int x, y;
};

//-----------------------------------------------------------------
//-----------------------------------------------------------------

struct exColor
{
	unsigned char mColor[4];
};
