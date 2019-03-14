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

namespace maths
{
	struct vector3f;
	struct quaternions;
}

struct camera3rdPerson
{
	float headHeight { 2.0f };
	float camHeight { 0.0f }; 
	float camDistance { -5.0f };
	float xSensitivity { 1.0f };
	float ySensitivity { 1.0f };
	
	Handle targetHandle;

	// not serialized, or maybe yes. not now though
	float orbit = 0.0f;
	float pivot = 0.0f;

	transform computeTransform() const;

	maths::vector3f computePosition() const;
	maths::quaternion computeRotation() const;
};

struct camera3rdPersonInput
{
	float horizontal;
	float vertical;
};

struct camera3rdPersonDriverSystem
{
	using components = mpl::List<camera3rdPerson, transform>;


	void update(camera3rdPerson & cam, transform & tr, float dt)
	{

		// cam.orbit += cam.xSensitivity * input.horizontal;
		// cam.pivot += cam.ySensitivity * input.horizontal;

		// tr.position = cam.computePosition();
		// tr.rotation = cam.computeRotation();

		tr = cam.computeTransform();

		// DEBUG << tr.rotation << "\n";
	}
};

