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
        vector3f a (-1, 0, 0);
        vector3f b (1, -1, 0);

        std::cout << maths::rad2deg * angle(a, b) << "\n";
        std::cout << maths::rad2deg * signedAngle(b, a) << "\n";

        return 0;
    }
}


int main()
{
    // return test();

    Engine engine;

    engine.initialize("Vastness", 1920, 1080);

    initializeGameComponents(engine.ecs);
    initializeGameSystems(engine.ecs);

    engine.ecsLoader->registerDeserializers(getGameDeserializeFunctions());

    engine.start();
    engine.terminate();
}
