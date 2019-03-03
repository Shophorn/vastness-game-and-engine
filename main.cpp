/*
Shophorn Games
Leo Tamminen
21/11/2018
*/

#include "Engine/Engine.hpp"
#include "Game/Components.hpp"

int main()
{
    Engine engine;

    engine.initialize("Vastness", 1920, 1080);

    initializeGameComponents(engine.ecs);
    initializeGameSystems(engine.ecs);

    engine.ecsLoader->registerDeserializers(getGameDeserializeFunctions());

    engine.start();
    engine.terminate();
}
