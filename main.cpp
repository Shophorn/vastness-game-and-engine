/*
Shophorn Games
Leo Tamminen
21/11/2018
*/

#include "Engine/Engine.hpp"
#include "Game/Components.hpp"

#include <iostream>
#include <iomanip>

#include "Engine/Maths/Maths.hpp"

namespace
{
    int test()
    {
        using namespace maths;
        using std::cout;

        vector3f vec0 (0, 1, 0);
        auto vec1 = quaternion::axisAngle(vector3f::up, deg2rad * 90) * vec0;
        auto vec2 = quaternion::axisAngle(vector3f::right, deg2rad * 90) * vec0;
        auto vec3 = quaternion::axisAngle(vector3f::left, deg2rad * 90) * vec0;
        cout << vec1 << "\n" << vec2 << "\n" << vec3;

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

    bool sceneLoaded = engine.loadScene("Game/game.json");
    
    // std::cout << "loaded";

    if (sceneLoaded)
    {
        engine.start();
    }

    engine.terminate();
}
