/*
Leo Tamminen
Created 27/12/2018
*/

#include "PlayerController.hpp"

using namespace Game;

void PlayerController::Update(float deltaTime)
{
    float step = deltaTime * moveSpeed;

    vec3 movement (Input::horizontal(), Input::vertical(), 0);
    float magnitude = glm::length(movement);
    if (magnitude > 1.0f)
    {
        movement /= magnitude;
    }
    movement *= step;

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
}
