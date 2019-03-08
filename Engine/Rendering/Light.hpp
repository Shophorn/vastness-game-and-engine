/*
Shophorn Games
Leo Tamminen
07/03/2019
*/

#pragma once

#include "../Color.hpp"
#include "../Maths/Maths.hpp"

enum class lightType
{
	DIRECTIONAL,
	POINT
};

struct Light
{
	color3f 	color {};
	float 		intensity { 1.0f };
	vector3f 	transform {};
	lightType 	type {};
};


class LightingManager
{
public:
	void addSerializedLighting(const serialization::Value & value);

	auto begin() { return _lights.begin(); }
	auto end() { return _lights.end(); }

	int count() { return _lights.size(); }

private:
	std::vector<Light> _lights;
};