#ifndef ENTITY_H
#define ENTITY_H

#include <iostream>
#include <string>
#include <unordered_map>
#include <memory>
#include <typeinfo>
#include <typeindex>
#include <string>
#include <cassert>
#include "components/components.h"

class Component;

class Entity
{
    std::unordered_map<std::type_index, std::shared_ptr<Component>> components;

public:
    template <typename T>
    void addComponent(std::shared_ptr<T> component);

    template <typename T>
    std::shared_ptr<T> getComponent();

    template <typename T>
    void removeComponent();
};

template <typename T>
void Entity::addComponent(std::shared_ptr<T> component)
{
    components[typeid(T)] = component;
}

template <typename T>
std::shared_ptr<T> Entity::getComponent()
{
    auto it = components.find(typeid(T));
    if (it != components.end())
    {
        return std::static_pointer_cast<T>(it->second);
    }
    return nullptr;
}

template <typename T>
void Entity::removeComponent()
{
    components.erase(typeid(T));
}

#endif