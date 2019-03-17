/*
Shophorn Unit Tests
Leo Tamminen
17/03/2019
*/

#pragma once

#include <vector>
#include <iostream>

#include "Quaternion.hpp"
#include "vector3f.hpp"
#include "Basic.hpp"

// these are tested against unity engines quaternion operations
// although if anyone asks, theyr'e not...

auto getVectorVector()
{
	return std::vector <vector3f>
	{
		vector3f(1, 0, 0),
		vector3f(0, 1, 0),
		vector3f(0, 0, 1),
		vector3f(127.861f, 98.653f, -44.074f),
		vector3f(132.619f, -129.692f, -155.190f),
		vector3f(-141.837f, -136.678f, -127.533f),
		vector3f(148.578f, 5.443f, 14.222f),
		vector3f(-95.122f, -34.035f, -160.352f),
		vector3f(60.210f, 96.942f, 67.476f),
		vector3f(168.672f, 8.029f, 9.783f),
		vector3f(-74.682f, -110.758f, -139.678f),
		vector3f(-158.901f, -107.914f, 125.738f),
		vector3f(-147.787f, -87.464f, -40.146f)
	};
}

void testEuler()
{
	auto vecs = getVectorVector();

	for (const auto & v : vecs)
	{
		std::cout << quaternion::eulerToQuaternion(v) << "\n";
	}
}

void testAxisAngle()
{
	for (const auto & v : getVectorVector())
	{
		float angle = 72 * maths::deg2rad;
		auto q = quaternion::axisAngle(normalize(v), angle);
		std::cout << q << "\n";
	}
}

void testMultiplication()
{
	auto vecs = getVectorVector();
	int  count = vecs.size();
	auto p = quaternion::axisAngle(normalize(vector3f(1, 1, 0)), maths::deg2rad * 67.0f);
	
	for (int i = 0; i < count; i++)
	{
		auto q = quaternion::axisAngle(normalize(vecs[i]), maths::deg2rad * 45.0f);
		std::cout << "#" << i << ": " << q * p << "\n";
	}
}

void testInverse()
{
	for (const auto v : getVectorVector())
	{
		auto q = quaternion::axisAngle(normalize(v), maths::deg2rad * 45.0);
		std::cout << q << "\t" << inverse(q) << "\n";
	}

}

void testVectorMultiplication()
{
	auto vecs = getVectorVector();
	int  count = vecs.size();
	auto q = quaternion::axisAngle(normalize(vector3f(1, 1, 0)), maths::deg2rad * 130.0f);

	for ( int i = 0; i < count; i++)
	{
		std::cout << "#" << i << ": " << q * vecs[i] << "\n";
	}
}

void testLookRotation()
{

}