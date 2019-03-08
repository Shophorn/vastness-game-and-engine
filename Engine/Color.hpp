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
	uint8_t r, g, b;
};

struct color32
{
	uint8_t r, g, b, a;

	color24 rgb () { return color24 {r, g, b}; }
};

struct color3f
{
	float r, g, b;
};

struct color4f
{
	float r, g, b, a;

	color3f rgb() { return color3f { r, g, b }; }
};

namespace serialization
{
	template<>
	inline color24 deserialize<color24> (const serialization::Value & value)
	{
		auto array = value.GetArray();
		return color24{
			static_cast<uint8_t>(array[0].GetInt()),
			static_cast<uint8_t>(array[1].GetInt()),
			static_cast<uint8_t>(array[2].GetInt())
		};
	}

	template<>
	inline color32 deserialize<color32> (const serialization::Value & value)
	{
		auto array = value.GetArray();
		return color32{
			static_cast<uint8_t>(array[0].GetInt()),
			static_cast<uint8_t>(array[1].GetInt()),
			static_cast<uint8_t>(array[2].GetInt()),
			static_cast<uint8_t>(array[3].GetInt())
		};
	}

	template<>
	inline color3f deserialize<color3f> (const serialization::Value & value)
	{
		auto array = value.GetArray();
		return color3f{
			array[0].GetFloat(),
			array[1].GetFloat(),
			array[2].GetFloat()
		};
	}

	template<>
	inline color4f deserialize<color4f> (const serialization::Value & value)
	{
		auto array = value.GetArray();
		return color4f{
			array[0].GetFloat(),
			array[1].GetFloat(),
			array[2].GetFloat(),
			array[3].GetFloat()
		};
	}
}
