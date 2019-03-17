/*
LeoTamminen
Created 24/02/2019
*/

#pragma once

namespace maths
{
    struct vector2f
    {
    	float x, y;

    	vector2f & operator += (vector2f rhs);
    	vector2f & operator -= (vector2f rhs);
    };
	inline vector2f operator + (vector2f lhs, vector2f rhs) { return lhs += rhs; }
	inline vector2f operator - (vector2f lhs, vector2f rhs) { return lhs -= rhs; }
}