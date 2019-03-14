#include "Camera3rdPerson.hpp"


#include "../../Engine/Serialization.hpp"
#include "../../Engine/ECS.hpp"
#include "../../Engine/EcsCoreComponents.hpp"
#include "../../Engine/Maths/Maths.hpp"
#include "../../Engine/SceneLoader.hpp" // for some reason, this must be included here, but 'followEntitySystem' does not need this.
										// corresponds to serialization::sceneloader

transform camera3rdPerson::computeTransform() const
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
	auto target = core::ecs.getComponent<transform>(targetHandle);
	auto pos = target.position + headHeight * vector3f::up + camDistance * vector3f::forward;

	transform tr;
	tr.position = pos;
	return tr;
/*
	auto pos = target.position;
	auto up = target.rotation * vector3f::up;
	pos += up * headHeight;

	auto forward = target.rotation * vector3f::forward;
	auto right = target.rotation * vector3f::right;
	*/
}



namespace serialization
{
	template<>
	camera3rdPerson deserialize(const Value & value)
	{
		camera3rdPerson cam;

		setIfHasMember(&cam.headHeight, "head height", value);
		setIfHasMember(&cam.camHeight, "cam height", value);
		setIfHasMember(&cam.camDistance, "cam distance", value);

		setIfHasMember(&cam.xSensitivity, "x sensitivity", value);
		setIfHasMember(&cam.ySensitivity, "y sensitivity", value);

		// ASSERT_HAS_FIELD(target)
		cam.targetHandle = serialization::sceneLoader->getMappedHandle(value["target"].GetInt());

		return cam;
	}
}