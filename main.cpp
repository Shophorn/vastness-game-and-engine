/*
Shophorn Games
Leo Tamminen
21/11/2018
*/

#include "Engine/Engine.hpp"
#include "Game/Components.hpp"


namespace
{
    int test()
    {
    }
}
int main()
{
//    return test();
    Engine engine;

    engine.initialize("Vastness", 1920, 1080);

    initializeGameComponents(engine.ecs);
    initializeGameSystems(engine.ecs);

    engine.ecsLoader->registerDeserializers(getGameDeserializeFunctions());

    engine.start();
    engine.terminate();
}
