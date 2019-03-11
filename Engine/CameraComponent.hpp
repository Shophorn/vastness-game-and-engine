/*
Shophorn visual department
Leo Tamminen
11/03/19
*/

#pragma once

#include "TransformComponent.hpp"
#include "DEBUG.hpp"
#include "Serialization.hpp"
#include "Maths/Maths.hpp"
#include "Rendering/RenderManager.hpp"

struct CameraComponent
{
	// vector3f clearColor;
	float fieldOfView;
	float nearClippingPlane;
	float farClippingPlane;
	float aspectRatio;
};

struct CameraUpdateSystem
{
	using components = mpl::List<CameraComponent, transform>;


	void onBeforeRender(CameraComponent cam, transform tr)
	{
		core::renderManager.updateCamera(cam, tr);
	}
};


namespace serialization
{
	template<>
	inline CameraComponent deserialize(const Value & value)
	{
		auto obj = value.GetObject();

		CameraComponent cam;

		if (obj.HasMember("field of view"))
			cam.fieldOfView = obj["field of view"].GetFloat();

		if (obj.HasMember("near clipping plane"))
			cam.nearClippingPlane = obj["near clipping plane"].GetFloat();

		if (obj.HasMember("far clipping plane"))
			cam.farClippingPlane = obj["far clipping plane"].GetFloat();

		if (obj.HasMember("aspect ratio"))
			cam.aspectRatio = obj["aspect ratio"].GetFloat();

		return cam;
	}
}