#ifndef USE_SYSTEM_H
#define USE_SYSTEM_H

#include <memory>
#include <vector>
#include <string>

class EntityManager;
class Entity;

class ItemSystem
{
    void ItemSystem::useTreasure(EntityManager &entityManager, std::shared_ptr<Entity> player, std::shared_ptr<Entity> treasure);
    void ItemSystem::useCompass(EntityManager &entityManager, std::shared_ptr<Entity> player, std::shared_ptr<Entity> compass);
    void ItemSystem::useBarrierSuit(EntityManager &entityManager, std::shared_ptr<Entity> player, std::shared_ptr<Entity> barrierSuit);

public:
    void update(EntityManager &entityManager, std::shared_ptr<Entity> player);
};

#endif