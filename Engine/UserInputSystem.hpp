/*
Shophorn Games
Leo Tamminen
Created 14/03/2019
*/

#pragma once

#include "Input.hpp"

struct UserInput
{
	// add info about controller instance
	// int controllerId;

	float vertical;
	float horizontal;
	// bitset<278> keys; // or something similar
};

struct UserInputSystem
{
	using components = mpl::List<UserInput>;

	void update(UserInput & input)
	{
		// get right input source from controller instance

		input.horizontal = core::input.horizontal();
		input.vertical = core::input.vertical();
	}	
};

#include "Serialization.hpp"

namespace serialization
{
	template<>
	inline UserInput deserialize(const Value & value)
	{
		return UserInput{};
	}
}