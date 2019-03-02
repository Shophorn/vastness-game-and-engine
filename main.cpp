/*
Shophorn Games
Leo Tamminen
21/11/2018
*/

#include "Engine/Engine.hpp"

int main()
{
    Engine engine;
    engine.initialize("Vastness", 1920, 1080);
    engine.start();
    engine.terminate();
}
