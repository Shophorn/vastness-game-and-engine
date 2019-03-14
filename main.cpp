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

        double pi = atan(1.0) * 4.0;
        std::cout << std::setprecision(30) << pi << "\n";

        vector3f vecs[] = {
            // vector3f(1, 0, 0.1),
            // vector3f(-1, 0, 0.1),
            vector3f(0, 1, 0),      // 00
            vector3f(0, -1, 0),     // 00
            // vector3f(0, 1, 1),
            // vector3f(0, 1, -1),
            // vector3f(1, 1, 1),
            // vector3f(1, 1, -1),
            // vector3f(0, 0, 1),
            // vector3f(0, 0, -1),
        };

        int count = sizeof(vecs) / sizeof(vecs[0]);
        for (int i = 0; i < count; i++)
        {
            cout << std::setprecision (3) << "#" << i << ": ";
            auto vec = normalize(vecs[i]);
            auto rot = lookRotation(vec);
            auto result = rot * vector3f::forward;

            cout << vec << "\t" << rot << "\t" << result << "\t" << (vec - result) << "\n";
        }

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
