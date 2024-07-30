#include "systems/item_system.h"
#include "entities/entity_manager.h"
#include "entities/entity.h"
#include "components/components.h"

void ItemSystem::useTreasure(EntityManager &entityManager, std::shared_ptr<Entity> player, std::shared_ptr<Entity> treasure)
{
    std::shared_ptr<TreasureComponent> treasureComponent = treasure->getComponent<TreasureComponent>();
    std::shared_ptr<GoldComponent> playerGoldComponent = player->getComponent<GoldComponent>();
    std::shared_ptr<GoldMultiplierComponent> multiplier = player->getComponent<GoldMultiplierComponent>();
    int gold = treasureComponent->value;

    if (multiplier) {
        gold *= multiplier->percent;
    }

    playerGoldComponent->gold += gold;
    entityManager.removeEntity(treasure);
}

void ItemSystem::useCompass(EntityManager &entityManager, std::shared_ptr<Entity> player, std::shared_ptr<Entity> compass)
{
    // Find stairs
    std::shared_ptr<Entity> stairs;
    for (auto &entity : entityManager.getEntities())
    {
        if (entity->getComponent<StairsComponent>())
        {
            stairs = entity;
            break;
        }
    }

    if (!stairs)
    {
        throw std::runtime_error("No stairs found when found compass");
    }

    stairs->getComponent<StairsComponent>()->visible = true;
    entityManager.removeEntity(compass);
}

void ItemSystem::useBarrierSuit(EntityManager &entityManager, std::shared_ptr<Entity> player, std::shared_ptr<Entity> barrierSuit)
{
    // Equip barrier suit
    player->addComponent(std::make_shared<BarrierSuitComponent>());
    entityManager.removeEntity(barrierSuit);
}

void ItemSystem::update(EntityManager &entityManager, std::shared_ptr<Entity> player)
{
    std::shared_ptr<ActionComponent> actionComponent = player->getComponent<ActionComponent>();
    if (!actionComponent->move)
        return;

    std::shared_ptr<PositionComponent> positionComponent = player->getComponent<PositionComponent>();
    std::shared_ptr<Entity> item;

    std::string &direction = player->getComponent<DirectionComponent>()->direction;
    if (direction == "no")
    {
        item = entityManager.getEntity(positionComponent->row - 1, positionComponent->col);
    }
    else if (direction == "so")
    {
        item = entityManager.getEntity(positionComponent->row + 1, positionComponent->col);
    }
    else if (direction == "ea")
    {
        item = entityManager.getEntity(positionComponent->row, positionComponent->col + 1);
    }
    else if (direction == "we")
    {
        item = entityManager.getEntity(positionComponent->row, positionComponent->col - 1);
    }
    else if (direction == "ne")
    {
        item = entityManager.getEntity(positionComponent->row - 1, positionComponent->col + 1);
    }
    else if (direction == "nw")
    {
        item = entityManager.getEntity(positionComponent->row - 1, positionComponent->col - 1);
    }
    else if (direction == "se")
    {
        item = entityManager.getEntity(positionComponent->row + 1, positionComponent->col + 1);
    }
    else if (direction == "sw")
    {
        item = entityManager.getEntity(positionComponent->row + 1, positionComponent->col - 1);
    }

    if (!item)
    {
        return;
    }

    std::shared_ptr<ItemTypeComponent> itemTypeComponent = item->getComponent<ItemTypeComponent>();
    if (!itemTypeComponent || !item->getComponent<CanPickupComponent>())
    {
        return;
    }

    if (itemTypeComponent->item_type == "treasure")
    {
        useTreasure(entityManager, player, item);
    }
    else if (itemTypeComponent->item_type == "compass")
    {
        useCompass(entityManager, player, item);
    }
    else if (itemTypeComponent->item_type == "barrier_suit")
    {
        useBarrierSuit(entityManager, player, item);
    }
}