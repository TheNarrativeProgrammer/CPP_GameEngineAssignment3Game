//
// * ENGINE-X
//
// + Types.h
// representations of: 2D vector with floats, 2D vector with integers and RBGA color as four bytes
//

#pragma once
#include <cmath>
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

	// Needed for velocity projection in collision response
	float Dot(const exVector2& OtherVector) const {
		return (x * OtherVector.x) + (y * OtherVector.y);
	}

	// Length of the vector for distance calculations
	float Length() const {
		return std::sqrt(x * x + y * y);
	}

	// returns a new unit vector
	exVector2 Normalize() const {
		float length = Length();
		return length > 0 ? exVector2{ x / length, y / length } : exVector2{ 0, 0 };
	}

	// Normalize the vector in place (modifies the existing vector)
	void NormalizeInPlace() {
		float length = Length();
		if (length > 0) {
			x /= length;
			y /= length;
		}
	}
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
