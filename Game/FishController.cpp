/*
LeoTamminen
Created 27/12/2018
*/

#include "FishController.hpp"
#include <stdio.h>

using namespace Game;

void FishController::Update(float deltaTime)
{
    transform->rotation += rotation * deltaTime;
}
