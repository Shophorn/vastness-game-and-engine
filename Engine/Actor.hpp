/*
Shophorn
Leo Tamminen
Created 27/12/2018
*/

#pragma once

class Actor
{
public:
    virtual void Update(float deltaTime) = 0;
    // TODO: do we need this?
    //    virtual ~Actor() = 0;
};