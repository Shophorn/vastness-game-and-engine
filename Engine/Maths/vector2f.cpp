/*
Shophorn Mathematics Department
Leo Tamminen
22/31/19
*/

#include "vector2f.hpp"

using namespace maths;

vector2f & vector2f::operator += (vector2f rhs)
{
	x += rhs.x;
	y += rhs.y;
	return *this;
}

vector2f & vector2f::operator -= (vector2f rhs)
{
	x -= rhs.x;
	y -= rhs.y;
	return *this;
}

// vector2f maths::operator + (vector2f lhs, vector2f rhs) const
// {
// 	return lhs += rhs;
// }

// vector2f maths::operator - (vector2f lhs, vector2f rhs) const
// {
// 	return lhs -= rhs;
// }

