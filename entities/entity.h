#include <iostream>
#include <string>
#include <unordered_map>
#include <memory>
#include <typeinfo>
#include <typeindex>
#include <string>
#include <cassert>

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