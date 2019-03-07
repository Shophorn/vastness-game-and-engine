/*
Shophorn Games
Leo Tamminen
07/03/2019
*/

#pragma once

#include "Serialization.hpp"

// todo do union
struct color24
{
	int8_t r, g, b;
};

struct color32
{
	int8_t r, g, b, a;

	color24 rgb () { return color24 {r, g, b}; }
};

namespace serialization
{
	template<>
	inline color32 deserialize<color32> (const serialization::Value & value)
	{
		auto array = value.GetArray();
		return color32{
			static_cast<int8_t>(array[0].GetInt()),
			static_cast<int8_t>(array[1].GetInt()),
			static_cast<int8_t>(array[2].GetInt()),
			static_cast<int8_t>(array[3].GetInt())
		};
	}
}
