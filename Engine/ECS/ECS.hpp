/*
LeoTamminen
Created 17/02/2019
*/

#pragma once

#include <functional>
#include <vector>
#include <unordered_map>
#include <utility>
#include <tuple>

#include "Handle.hpp"
#include "HandleManager.hpp"
#include "List.hpp"
#include "Component.hpp"

#include "../DEBUG.hpp"


#include "Component.hpp"




/// Detect interesting fields
// S for System
namespace detail
{
    template<typename S, typename... Args>
    constexpr decltype(std::declval<S>().update(std::declval<Args>()...), true) hasUpdate(int) { return true; }

    template<typename S, typename... Args>
    constexpr bool hasUpdate(...) { return false; }

    template <typename S>
    constexpr decltype(std::declval<typename S::components>, true) hasComponents(int){ return true; }

    template <typename S>
    constexpr bool hasComponents (...) { return false;}


    template <typename S, typename T, typename Cs>
    struct hasComponentTimeUpdateHelper;

    template <typename S, typename T, typename ... Cs>
    struct hasComponentTimeUpdateHelper<S, T, mtl::List<Cs...>>
    {
        static constexpr bool value = detail::hasUpdate<S, Cs&..., T>(0);
    };

    template <typename S, typename Cs>
    struct hasComponentUpdateHelper;

    template <typename S, typename ... Cs>
    struct hasComponentUpdateHelper<S, mtl::List<Cs...>>
    {
        static constexpr bool value = detail::hasUpdate<S, Cs&...>(0);
    };

}
template <typename System, typename T>
constexpr bool hasEcsUpdate = detail::hasUpdate<System, T>(0);

template <typename System>
constexpr bool hasComponents = detail::hasComponents<System>(0);


template <typename System, typename Components, typename T>
constexpr bool hasComponentTimeUpdate = detail::hasComponentTimeUpdateHelper<System, T, Components>::value;

template <typename System, typename Components>
constexpr bool hasComponentUpdate = detail::hasComponentUpdateHelper<System, Components>::value;
///-------------------------------------------------------

class ecs
{
    using updateHandler  = std::function < void (float) >;

    std::vector<updateHandler> updateHandlers;

    std::vector<ComponentInterface*> components;
    std::unordered_map< const std::type_info*, ComponentInterface *> componentMap;

    HandleManager handleManager;

    // todo: use this to remove entities
    // std::vector<Handle> deadHandles;


public:
    template <typename System, typename ... TArgs>
    System * registerSystem(TArgs ... args)
    {
        auto * system = new System { std::forward<TArgs>(args) ... };

        if constexpr (hasEcsUpdate<System, float>)
        {
            registerPlainUpdate(system);
        }

        if constexpr (hasComponents<System>)
        {
            using componentList = typename System::components;

            if constexpr (hasComponentTimeUpdate<System, componentList, float>)
                registerComponentTimeUpdate(system, componentList());

            if constexpr (hasComponentUpdate<System, componentList>)
                registerComponentUpdate(system, componentList());

        }

        return system;
    }

    template <typename System>
    void registerPlainUpdate(System * system)
    {
        registerUpdate( [&system](float dt) {system->update(dt);});
    }

    template <int> void Impl_getHandles(std::vector<Handle> & handles) {}

    template <int index, typename First, typename ... Others>
    void Impl_getHandles(std::vector<Handle> & handles)
    {
        auto otherHandles = componentMap[&typeid(First)]->getHandles();
        int stop = (int)handles.size();
        for (int i = 0; i < stop; i++)
        {
            if (std::find(otherHandles.begin(), otherHandles.end(), handles[i]) == otherHandles.end())
            {
                // remove by swapping this to last
                handles[i] = handles[stop - 1];
                stop--;
                i--;
            }
        }

        while (handles.size() > stop)
        {
            handles.pop_back();
        }

        Impl_getHandles<index + 1, Others...>(handles);
    }

    template <typename First, typename ... Others>
    std::vector<Handle> getHandles()
    {
        auto handles = componentMap[&typeid(First)]->getHandles();
        Impl_getHandles<0, Others...>(handles);
        return handles;
    }

    template <typename CompSequence>
    CompSequence & getComponentSequence(Handle handle)
    {
        return componentMap[&typeid(CompSequence)]->get<CompSequence>(handle);
    }

    template <typename System, typename ... Components>
    void registerComponentTimeUpdate(System *system, mtl::List<Components...> &&)
    {
        cout << "register update with time\n";

        registerUpdate([=](float dt)
        {
            for (auto h : getHandles<Components...>())
                system->update(getComponentSequence<Components>(h)..., dt);
        });
    }

    template <typename System, typename ... Components>
    void registerComponentUpdate(System * system, mtl::List<Components...>&&)
    {
        cout << "register update with no time\n";

        registerUpdate([=](float dt)
        {
           for (auto h : getHandles<Components...>())
               system->update(getComponentSequence<Components>(h)...);
        });
    }

    void registerUpdate(updateHandler && handler)
    {
        updateHandlers.emplace_back(handler);
    }


    /// Components --------------------------------------------
    template <typename Component, typename ... TArgs>
    void addComponent(Handle entity, TArgs ... args)
    {
        ComponentInterface * c = getInterface<Component>();
        c->add<Component>(entity, args...);
    }

    template <typename Component>
    void registerComponent()
    {
        // Add only once
        if (componentMap.find(&typeid(Component)) != componentMap.end())
            return;

        auto * component = new ComponentInterface;
        component->storage = new ComponentStorageHandler<Component>;

        components.emplace_back(component);
        componentMap[&typeid(Component)] = component;
    }

    template <typename Component>
    ComponentInterface * getInterface()
    {
        assert(componentMap.find(&typeid(Component)) != componentMap.end() && "Unregistered Component type");
        return componentMap[&typeid(Component)];
    }

    template <typename Component>
    Component & getComponent(Handle entity)
    {
        assert(componentMap.find(&typeid(Component)) != componentMap.end() && "Unregistered Component type");
        return componentMap[&typeid(Component)]->get<Component>(entity);
    }

    Handle createEntity()
    {
        return handleManager.create();
    }

    void initialize() {}

    void update(float deltaTime)
    {
        for (auto update : updateHandlers)
            update(deltaTime);
    }
};
