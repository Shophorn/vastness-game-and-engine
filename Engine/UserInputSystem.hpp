/*
Shophorn Games
Leo Tamminen
Created 14/03/2019
*/

#pragma once

#include "Input.hpp"
#include "Maths/Maths.hpp"

#include "DEBUG.hpp"

struct UserInput
{
	// add info about controller instance
	const int controllerId { 0 };

	float vertical;
	float horizontal;

	vector2f mouseDelta;
	// bitset<278> keys; // or something similar
};

struct UserInputSystem
{
	using components = mpl::List<UserInput>;

	void update(UserInput & input)
	{
		// get right input source from controller instance
		// core::input.setController(input.controllerId); // this could be better but probably not thread safe
		input.horizontal 	= core::input.horizontal(input.controllerId);
		input.vertical 		= core::input.vertical(input.controllerId);
		input.mouseDelta 	= core::input.mouseMovement(input.controllerId);
	}	
};

#include "Serialization.hpp"

namespace serialization
{
	template<>
	inline UserInput deserialize(const Value & value)
	{
		// todo
		// int controller = core::input.createorgetcontrollersomehow()

		return UserInput{};
	}
}