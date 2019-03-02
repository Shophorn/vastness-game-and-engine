/*
Shophorn Games
Leo Tamminen
Created 13/02/2019
*/

#pragma once

#include <unordered_map>
#include <string>

class GLFWwindow;
class rendererSystem;

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

    bool isRunning() { return _isRunning; }
};


