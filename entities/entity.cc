#include "entity.h"
#include "component.h"

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