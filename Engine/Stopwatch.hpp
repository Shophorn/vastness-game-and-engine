/*
LeoTamminen
Created 25/02/2019
*/

#pragma once

#include <chrono>

class Stopwatch
{
    using clock = std::chrono::high_resolution_clock;
    using timePoint = clock::time_point;
public:
    static Stopwatch startNew()
    {
        return Stopwatch {clock::now()};
    };

    float seconds ()
    {
        using namespace std::chrono;
        auto end = clock::now();
        return duration_cast<duration<float>>(end - _start).count();
    }

private:
    Stopwatch (timePoint start) : _start(start) {}
    timePoint _start;
};