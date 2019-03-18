/*
Shophorn Games
Leo Tamminen
18/03/19
*/

#pragma once

#include "Serialization.hpp"
#include "ECS.hpp"
#include "EcsCoreComponents.hpp"
#include "Maths/Maths.hpp"
#include "SceneLoader.hpp" // for some reason, this must be included here, but 'followEntitySystem' does not need this.
										// corresponds to serialization::sceneloader

#include "DEBUG.hpp"

struct CameraController3rdPerson
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

	transform computeTransform(transform target) const;
	quaternion baseRotation() const;
};

struct CameraController3rdPersonSystem
{
	using components = mpl::List<CameraController3rdPerson, transform, UserInput>;

	void update(CameraController3rdPerson & controller, transform thisTransform, UserInput & input, float dt)
	{
		controller.orbit += controller.xSensitivity * input.mouseDelta.x * dt;
		controller.pivot += controller.ySensitivity * input.mouseDelta.y * dt;

		transform & cam = core::ecs.getComponent<transform>(controller.targetHandle);
		cam = controller.computeTransform(thisTransform);
	}
};

#include "Serialization.hpp"

namespace serialization
{
	template <>
	inline CameraController3rdPerson deserialize <CameraController3rdPerson>(const Value & value)
	{
		// ASSERT_HAS_FIELD(target)
		CameraController3rdPerson controller;
		controller.targetHandle = serialization::sceneLoader->getMappedHandle(value["target"].GetInt());

		setIfHasMember(&controller.headHeight, "head height", value);
		setIfHasMember(&controller.camHeight, "cam height", value);
		setIfHasMember(&controller.camDistance, "cam distance", value);

		setIfHasMember(&controller.xSensitivity, "x sensitivity", value);
		setIfHasMember(&controller.ySensitivity, "y sensitivity", value);

		return controller;
	}
}


// stupid call, fix
inline transform CameraController3rdPerson::computeTransform(transform target) const
{
	// move POS to target
	// move POS headHeight amount UP ( = target's up )
	// rotate FORWARD and RIGHT orbit amount around UP
	// rotate FORWARD and UP pivot amount around RIGHT
	// move POS camDistance amount to FORWARD ( in most cases, camDistance should be negative, so CAM moves back)
	// move POS camHeight amount to UP
	// set transform position to POS
	// set transform rotation to quaternion::lookRotation(FORWARD, UP)

	// this should be copy, that we can modify, and move back out
	// auto target = core::ecs.getComponent<transform>(targetHandle);

	// instead use targets up
	auto up = target.rotation * vector3f::up;
	auto orbitRotation = quaternion::axisAngle(up, orbit);
	// auto right = orbitRotation * vector3f::right;
	auto pivotRotation = quaternion::axisAngle(vector3f::right, pivot);

	auto forward = orbitRotation * pivotRotation * vector3f::forward;

	auto pos = target.position + headHeight * up + forward * camDistance;
	
	up = pivotRotation * up;
	// DEBUG << up << ", " << magnitude(up) << ", " << dot (up, vector3f::up) <<  "\n";


	transform tr;
	tr.position = pos;

	tr.rotation = quaternion::lookRotation(forward, up);
	// tr.rotation = orbitRotation * pivotRotation;
	return tr;

}