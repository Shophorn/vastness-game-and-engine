/*
Leo Tamminen
Created 27/12/2018
*/

#include "PlayerController.hpp"

using namespace Game;

void PlayerController::Update(float deltaTime)
{
    float step = deltaTime * moveSpeed;
    transform->position += vec3(Input::horizontal() * step, Input::vertical() * step, 0);
}
