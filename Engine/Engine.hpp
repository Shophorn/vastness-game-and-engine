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
public:
    Engine() = default;
    ~Engine() = default;

    void initialize(const char * title, int width, int height);
    bool loadScene(const char * path);
    void start();
    void terminate();

    // merely a reference, maybe like borrowed_ptr
    ECS * ecs = nullptr;
    std::unique_ptr<SceneLoader> ecsLoader = nullptr;

private:
    GLFWwindow * _window = nullptr;
    
    bool _isRunning = false;
    float _lastTime = 0.0f;
    float _deltaTime = 0.0f;

    void handleEvents();
    void update();
    void render();
};
