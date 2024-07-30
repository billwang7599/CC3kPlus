#ifndef ENTITY_MANAGER_H
#define ENTITY_MANAGER_H

#include <vector>
#include <memory>
#include <utility>
#include <algorithm>
#include "entities/entity.h"
#include "components/position_component.h"

class Entity;
class Component;
class PositionComponent;

class EntityManager
{
private:
    std::vector<std::shared_ptr<Entity>> entities;

public:
    std::shared_ptr<Entity> createEntity();
    void removeEntity(std::shared_ptr<Entity> entity);
    std::shared_ptr<Entity> getEntity(int row, int col);
    std::vector<std::shared_ptr<Entity>> &getEntities();
};

#endif