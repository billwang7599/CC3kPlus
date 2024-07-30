#include "systems/item_system.h"
#include "entities/entity_manager.h"
#include "entities/entity.h"
#include "components/components.h"
#include "constants/constants.h"

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
    player->addComponent(std::make_shared<CompassComponent>());
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

    std::string &direction = player->getComponent<DirectionComponent>()->direction;

    int row = positionComponent->row + DIRECTION_MAP.at(direction).first;
    int col = positionComponent->col + DIRECTION_MAP.at(direction).second;
    std::shared_ptr<Entity> item = entityManager.getEntity(row, col);
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