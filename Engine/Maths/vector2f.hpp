/*
LeoTamminen
Created 24/02/2019
*/

#pragma once

namespace maths
{
    class vector2f
    {
    public:
        float &operator[](int index) { return _values[index]; }

    private:
        float _values[2];
    };
}