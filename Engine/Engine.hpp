/*
Shophorn Games
Leo Tamminen
Created 13/02/2019
*/

#pragma once

#include <unordered_map>
#include <string>

class GLFWwindow;

class Engine
{
private:
    bool _isRunning;
    GLFWwindow * _window;


public:
    Engine() = default;
    ~Engine() = default;

    void initialize(const char *title, int width, int height);

    void handleEvents();
    void update();
    void render();
    void terminate();

    bool isRunning() { return _isRunning; }
};


