/*
Shophorn Games
Leo Tamminen
Created 03/03/2019
*/

/*
quaternions represent rotation.
in all operations expect radians as angle inputs. As of writing this, its not so though.
*/

#pragma once

#include "vector3f.hpp"

namespace maths
{
    // struct vector3f;
    struct matrix4f;

    struct quaternion
    {
        float x = 0, y = 0, z = 0, w = 1;

        static const quaternion identity;

        quaternion (float x, float y, float z, float w);
        quaternion(vector3f xyz, float w);

        vector3f    operator * (vector3f rhs) const;
        quaternion  operator * (quaternion rhs) const;

        static quaternion axisAngle(vector3f axis, float angle);
        static quaternion lookRotation(vector3f forward, vector3f up = vector3f::up);
        static quaternion eulerToQuaternion(vector3f euler);
        static matrix4f   toRotationMatrix(quaternion q);

    private:
        vector3f xyz() const; // for debug now. Maybe make union to use as such
    };

    inline const quaternion quaternion::identity = quaternion{0,0,0,1};
    float magnitude(quaternion);
    quaternion inverse(quaternion q);
}