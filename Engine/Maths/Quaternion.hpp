/*
Shophorn Games
Leo Tamminen
Created 03/03/2019
*/

#pragma once

namespace maths
{
    struct quaternion
    {
        float x, y, z, w;

        static const quaternion identity;
    };

    inline const quaternion quaternion::identity = quaternion{0,0,0,1};

    bool isUnitQuaternion(quaternion q);

    struct vector3f;
    struct matrix4f;

    quaternion eulerToQuaternion(vector3f euler);
    matrix4f toRotationMatrix(quaternion q);
    quaternion inverse(quaternion q);
}