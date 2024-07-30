#ifndef MOVEMENT_SYSTEM_H
#define MOVEMENT_SYSTEM_H


#include "entities/entity_manager.h"
#include <string>

class MovementSystem {
    bool moveEntity(EntityManager& entities, Entity&, std::string& direction);
    void moveEnemy(EntityManager& entities, Entity&);
    void freezeEnemies(EntityManager& entities, Entity&);
    public:
    void update(EntityManager&, std::shared_ptr<Entity>);
};
#endif // MOVEMENT_SYSTEM_H
