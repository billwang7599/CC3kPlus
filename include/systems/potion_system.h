#ifndef POTION_SYSTEM_H
#define POTION_SYSTEM_H

#ifndef USE_SYSTEM_H
#define USE_SYSTEM_H

#include <memory>
#include <vector>
#include <string>

class EntityManager;
class Entity;

class PotionSystem
{
    void usePotion(EntityManager &entityManager, std::shared_ptr<Entity> player, std::shared_ptr<Entity> potion);

public:
    void update(EntityManager &entityManager, std::shared_ptr<Entity> player);
};

#endif
#endif // POTION_SYSTEM_H
