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

#include "Engine/Maths/QuaternionTests.hpp"

namespace
{
    int test()
    {
        // testEuler();                 // FAIL
        // testLookRotation()           // PENDING
        // testAxisAngle();             // PASS
        // testMultiplication();        // PASS
        // testInverse();               // PASS
        // testVectorMultiplication();  // PASS
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
