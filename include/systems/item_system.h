#ifndef ITEM_SYSTEM_H
#define ITEM_SYSTEM_H

#include <memory>
#include <vector>
#include <string>

class EntityManager;
class Entity;

class ItemSystem
{
    void useTreasure(EntityManager &entityManager, std::shared_ptr<Entity> player, std::shared_ptr<Entity> treasure);
    void useCompass(EntityManager &entityManager, std::shared_ptr<Entity> player, std::shared_ptr<Entity> compass);
    void useBarrierSuit(EntityManager &entityManager, std::shared_ptr<Entity> player, std::shared_ptr<Entity> barrierSuit);

public:
    void update(EntityManager &entityManager, std::shared_ptr<Entity> player);
};

#endif