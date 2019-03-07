/*
Shophorn
Leo Tamminen
13/02/2019
*/

#pragma once

#include <cmath>

namespace maths
{
	using std::abs;
	using std::sqrt;
	using std::cos;
	using std::sin;
	using std::acos;
	
    inline constexpr float pi = 3.14159265359f;
    inline constexpr float deg2rad = pi / 180.0f;
    inline constexpr float rad2deg = 180.0f / pi;

    // returns 1 if value >= 0, else -1
    template <typename T>
    T sign(T value)
    {
    	return (value >= 0) * 2 - 1;
    }
}