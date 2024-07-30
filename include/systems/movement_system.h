
#include "entities/entity_manager.h"
#include <string>

class MovementSystem {
    bool moveEntity(EntityManager& entities, Entity&, std::string& direction);
    void moveEnemy(EntityManager& entities, Entity&);
    void freezeEnemies(EntityManager& entities, Entity&);
    public:
    void update(EntityManager&, std::shared_ptr<Entity>);
};