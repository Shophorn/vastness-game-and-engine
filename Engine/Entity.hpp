/*
Shophorn
Leo Tamminen
Created 27/12/2018
*/

#pragma once

class Entity
{
public:
    virtual ~Entity() = default;

    virtual void update(float deltaTime) = 0;
    virtual void start() = 0;
};