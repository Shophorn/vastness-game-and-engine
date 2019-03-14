// #include "TransformComponent.hpp"


// matrix4f modelMatrix(const transform & tr)
// {
//     // todo calculate manually
//     matrix4f T = matrix4f::translate(tr.position);
//     matrix4f R = maths::toRotationMatrix(tr.rotation);
//     matrix4f S = matrix4f::scale(tr.scale);

//     return T * R * S;
// }

// matrix4f inverseModelMatrix(const transform & tr)
// {
//     using namespace maths;

//     matrix4f IT = matrix4f::translate(-tr.position);
//     matrix4f IR = toRotationMatrix(inverse(tr.rotation));
//     vector3f inverseScale ( 1.0f/ tr.scale.x, 1.0f / tr.scale.y, 1.0f / tr.scale.z);
//     matrix4f IS = matrix4f::scale(inverseScale);

//     return IS * IR * IT;
// }

// namespace serialization
// {
//     template <>
//   	transform deserialize<transform>(const Value & value)
//     {
//         transform result;
//         if (value.HasMember("position"))
//             result.position = deserialize<vector3f>(value["position"]);

//         if (value.HasMember("rotation"))
//             result.rotation = eulerToQuaternion(deserialize<vector3f>(value["rotation"]));

//         else if (value.HasMember("direction"))
//         {
//             auto forward = deserialize<vector3f>(value["direction"]);
//             forward = normalize(forward);
//             auto rot = lookRotation(forward);
//             result.rotation = rot;//lookRotation(normalize(deserialize<vector3f>(value["direction"])));
//         }

//         if (value.HasMember("scale"))
//             result.scale = deserialize<vector3f>(value["scale"]);

//         return result;
//     }
// }
