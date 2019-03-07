/*
Shophorn Games
Leo Tamminen
07/03/2019
*/

#pragma once

#include "../Color.hpp"
#include "../Serialization.hpp"
// #include "RenderManager.hpp"


enum class lightType
{
	DIRECTIONAL = 0
};

struct light
{
	color32 color;
	float intensity;
	lightType type;
};

namespace serialization
{
	template<>
	inline light deserialize <light>(const serialization::Value & value)
	{
		lightType type;
		auto typeString = value["light type"].GetString();
		if (typeString == "DIRECTIONAL")
			type = lightType::DIRECTIONAL;

		light l {
			deserialize<color32> (value["color"]),
			value["intensity"].GetFloat(),
			type
		};

		// core::renderManager.registerLight(l);

		return l;
	}
}
