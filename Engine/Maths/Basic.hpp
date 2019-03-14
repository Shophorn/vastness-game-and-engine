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
    using std::atan;
    using std::atan2;
	
    // inline constexpr float pi = 3.14159265359f;
    constexpr double pi = atan(1.0) * 4.0;
    constexpr float deg2rad = pi / 180.0f;
    constexpr float rad2deg = 180.0f / pi;

    // returns 1 if value >= 0, else -1
    template <typename T>
    T zeroPositiveSign(T value)
    {
    	return (value >= 0) * 2 - 1;
    }

    // returns 1 if value is positive, 0 if 0, else - 1
    template <typename T>
    T zeroZeroSign(T value)
    {
        return (value > 0) - (value < 0);
    }

    template <typename T>
    T zeroNegativeSign(T value)
    {
        return (value > 0) * 2 - 1;
    }
}