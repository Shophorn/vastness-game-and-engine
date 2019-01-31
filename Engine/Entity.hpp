/*
Shophorn
Leo Tamminen
Created 27/12/2018
*/

#pragma once

class Entity
{
public:
    virtual void Update(float deltaTime) = 0;
    // TODO: do we need this?
    //    virtual ~Entity() = 0;
};

//struct EntityInstance
//{
//    Entity * entity;
//    Transform * transform;
//    Renderer * renderer;
//};
//
//class EntityManager
//{
//    EntityInstance * entities;
//    int count;
//
//    void UpdateEntities (float deltaTime)
//    {
//        for (int i = 0; i < count; i++)
//        {
//            entities[i].entity->Update(deltaTime);
//        }
//    };
//};