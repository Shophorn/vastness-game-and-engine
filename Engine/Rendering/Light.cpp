#include "../StringOperations.hpp"

#include "Light.hpp"
#include "../Serialization.hpp"

namespace serialization
{
	constexpr auto * keyword_color 		= "color";
	constexpr auto * keyword_intensity 	= "intensity";
	constexpr auto * keyword_transform	= "transform";
	constexpr auto * keyword_type 		= "type";

	lightType lightTypeFromString(const char * str)
	{
		using namespace strOps;

		if (equals(str, "DIRECTIONAL"))
			return lightType::DIRECTIONAL;

		if (equals(str, "POINT"))
			return lightType::POINT;

		return static_cast<lightType> (-1);
	}

	template<>
	Light deserialize <Light> (const serialization::Value & value)
	{
		Light light;

		if (value.HasMember(keyword_color))
			light.color = deserialize < decltype(Light::color) >(value[keyword_color]);

		if (value.HasMember(keyword_intensity))
			light.intensity = value[keyword_intensity].GetFloat();

		if (value.HasMember(keyword_transform))
			light.transform = normalize(deserialize < decltype(Light::transform) > (value[keyword_transform]));

		if (value.HasMember(keyword_type))
			light.type = lightTypeFromString(value[keyword_type].GetString());

		return light;
	}
}

void LightingManager::addSerializedLighting(const serialization::Value & value)
{
	for (const auto & subValue : value.GetArray())
	{
		_lights.emplace_back(serialization::deserialize<Light>(subValue));
	}
}
