/*
Leo Tamminen
Created 27/12/2018
*/

#include "PlayerController.hpp"
#include "../Engine/Maths/Vector3f.hpp"

using namespace Game;
using namespace Engine::Maths;

void PlayerController::Update(float deltaTime)
{
    float step = deltaTime * moveSpeed;

    Vector3f movement (Input::horizontal(), Input::vertical(), 0);
    float magnitude = Maths::magnitude(movement);
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

    camera->position = transform->position + cameraOffset;
    camera->target = transform->position;
}
