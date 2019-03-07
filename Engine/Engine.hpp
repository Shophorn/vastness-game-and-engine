/*
Shophorn Games
Leo Tamminen
Created 13/02/2019
*/

#pragma once

#include <unordered_map>
#include <string>
#include <memory>

#include "Serialization.hpp"
#include "SceneLoader.hpp"

class GLFWwindow;
class rendererSystem;
class ECS;



class Engine
{
private:
    bool _isRunning;
    GLFWwindow * _window = nullptr;

    void handleEvents();
    void update();
    void render();

public:
    Engine() = default;
    ~Engine() = default;

    void initialize(const char *title, int width, int height);
    void start();
    void terminate();

    // merely a reference, maybe like borrowed_ptr
    ECS * ecs = nullptr;
    std::unique_ptr<SceneLoader> ecsLoader = nullptr;
};
