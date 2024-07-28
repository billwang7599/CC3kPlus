#include "entity_manager.h"
#include "entity.h"
#include "component.h"
#include "position_component.h"

std::shared_ptr<Entity> EntityManager::createEntity()
{
    auto entity = std::make_shared<Entity>();
    entities.push_back(entity);
    return entity;
}

void EntityManager::removeEntity(std::shared_ptr<Entity> entity)
{
    // moves all elements equal to entity to the end of the vector and returns an iterator to the new end of the vector, then erase
    entities.erase(std::remove(entities.begin(), entities.end(), entity), entities.end());
}

std::shared_ptr<Entity> EntityManager::getEntity(int row, int col)
{
    for (auto entity : entities)
    {
        auto position_component = entity->getComponent<PositionComponent>();

        if (!position_component)
        {
            continue;
        }

        if (position_component->row == row && position_component->col == col)
        {
            return entity;
        }
    }
    return nullptr;
}