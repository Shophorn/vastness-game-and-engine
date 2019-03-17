/*
Shophorn Games
Leo Tamminen
Created 14/03/2019
*/

/*
	B is base, tracks players absolute position.
	h is head level, although it doesn't need to be exactly on head level.
	headHeight is distance of h from B directly up.

	C is camera itself pointing directly forward.
	h to d is camDistance, that is horizontal distance from head in neutral look position.
	d to C is camHeight, vertical distance from head in neutral position.

			<- C
	 h---------d
	|
	|				
	B


	View is rotated horizontally by rotating around [Bh] - axis and vertically
	pivoting around rotated x - axis of h.

*/

#pragma once

#include "../../Engine/ECS.hpp"
#include "../../Engine/TransformComponent.hpp"
#include "../../Engine/DEBUG.hpp"
#include "../../Engine/EcsCoreComponents.hpp"

namespace maths
{
	struct vector3f;
	struct quaternions;
}

static constexpr float maxPivot = maths::deg2rad * 70;

struct camera3rdPerson
{
	float headHeight { 2.0f };
	float camHeight { 0.0f }; 
	float camDistance { -5.0f };
	float xSensitivity { 0.3f };
	float ySensitivity { 0.3f };

	Handle targetHandle;

	// not serialized, or maybe yes. not now though
	float orbit = 0.0f;
	float pivot = 0.0f;

	transform computeTransform() const;
};

struct camera3rdPersonDriverSystem
{
	using components = mpl::List<camera3rdPerson, transform, UserInput>;

	void update(camera3rdPerson & cam, transform & tr, UserInput input, float dt)
	{
		cam.orbit += cam.xSensitivity * input.mouseDelta.x * dt;
		cam.pivot += cam.ySensitivity * input.mouseDelta.y * dt;
		tr = cam.computeTransform();
	}
};