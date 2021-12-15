#pragma once

#include <math.h>

#define PI 3.14159265359

struct vector_2D
{
	float x;
	float y;

	vector_2D(float x = 0, float y = 0) : x(x), y(y) { }
	
	vector_2D& operator=(const vector_2D& v)
	{
		x = v.x;
		y = v.y;
		return *this;
	}

	vector_2D operator=(const float f)
	{
		x = f;
		y = f;
		return vector_2D(x, y);
	}

	vector_2D operator+(const vector_2D& v)
	{
		return vector_2D(v.x + x, v.y + y);
	}

	vector_2D& operator+=(const vector_2D& v)
	{
		this->x += v.x;
		this->y += v.y;
		return *this;
	}

	vector_2D& operator-=(const vector_2D& v)
	{
		this->x -= v.x;
		this->y -= v.y;
		return *this;
	}

	vector_2D operator-(const vector_2D& v)
	{
		return vector_2D(x - v.x, y - v.y);
	}

	vector_2D operator*(const float f)
	{
		return vector_2D(f * x, f * y);
	}

	float operator*(vector_2D v)
	{
		return v.x * x + v.y * y;
	}

	vector_2D operator/(float f)
	{
		return vector_2D(x / f, y / f);
	}

};

