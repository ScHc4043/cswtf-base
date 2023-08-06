#pragma once
#include <math.h>

//Vector2 struct
struct Vector2
{
	//Struct's data
	float x, y;

	//Operators, all self explanatory
	Vector2 operator+ (Vector2 Other)
	{
		return Vector2(this->x + Other.x, this->y + Other.y);
	}

	Vector2 operator- (Vector2 Other)
	{
		return Vector2(this->x - Other.x, this->y - Other.y);
	}

	Vector2 operator* (float Numerator)
	{
		return Vector2(this->x * Numerator, this->y * Numerator);
	}

	Vector2 operator/ (float Numerator)
	{
		return Vector2(this->x / Numerator, this->y / Numerator);
	}

	bool IsNull()
	{
		return this->x == 0.f && this->y == 0.f;
	}
};

//Vector3 struct
struct Vector3
{
	//Struct's data
	float x, y, z;

	//Operators, all self explanatory
	Vector3 operator+ (Vector3 Other)
	{
		return Vector3(this->x + Other.x, this->y + Other.y, this->z + Other.z);
	}

	Vector3 operator- (Vector3 Other)
	{
		return Vector3(this->x - Other.x, this->y - Other.y, this->z - Other.z);
	}

	Vector3 operator* (float Numerator)
	{
		return Vector3(this->x * Numerator, this->y * Numerator, this->z * Numerator);
	}

	Vector3 operator/ (float Numerator)
	{
		return Vector3(this->x / Numerator, this->y / Numerator, this->z / Numerator);
	}

	bool IsNull()
	{
		return this->x == 0.f && this->y == 0.f && this->z == 0.f;
	}
};

//Our math class
class CMath
{
public:
	Vector3 CalculateAngle(Vector3 Local, Vector3 Target)
	{
		Vector3 ReturnAngle = Vector3();

		//Get delta of the angles
		Vector3 Delta = Local - Target;

		//Calculate hypot (longest side of a triangle for all of you year 4s)
		float Hypothenuse = sqrtf(Delta.x * Delta.x + Delta.y * Delta.y + Delta.z * Delta.z);

		//Pitch
		ReturnAngle.x = asinf(Delta.z / Hypothenuse) * (180.0f / 3.1415926f);

		//Yaw
		ReturnAngle.y = atanf(Delta.y / Delta.x) * (180.0f / 3.1415926f);

		//Roll
		ReturnAngle.z = 0.f;

		return ReturnAngle;
	}
};
