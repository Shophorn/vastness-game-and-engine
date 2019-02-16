/*
Leo Tamminen
Created 27/12/2018
*/

#include "PlayerController.hpp"
#include "../Engine/Maths/Vector3f.hpp"
#include "../Engine/Serialization.hpp"

#include <iostream>

using namespace Game;
using namespace Core;
using namespace Core::Maths;

void PlayerController::update(float deltaTime)
{
    float step = deltaTime * moveSpeed;

    Vector3f movement (Input::horizontal(), Input::vertical(), 0);
    float magnitude = Maths::magnitude(movement);
    if (magnitude > 1.0f)
    {
        movement /= magnitude;
    }
    movement *= step;

//    Collider moved {transform->position + movement, collider.radius};
//    if (CollisionManager::testCollisions(moved))
//    {
//        movement = Vector3f(0);
//    }
    transform->position += movement;

    if (magnitude > 0) {
        animator->SetAnimation(1);

    } else {
        animator->SetAnimation(0);
    }

    if (movement.x != 0)
    {
        transform->scale.x = movement.x < 0 ? -1 : 1;
    }

    animator->Update(deltaTime);

    camera->position = transform->position + cameraOffset;
    camera->target = transform->position;



}

void PlayerController::start()
{
//    CollisionManager::addCollider(&collider);
}

namespace Core::Serialization
{
    template<>
    PlayerController deserialize<PlayerController>(const Value &value)
    {
        PlayerController p = PlayerController();
        p.moveSpeed = value["move speed"].GetFloat();
//        p.collider = deserialize<Collider>(value["collider"]);
        return p;
    }
}
