#include "spawn_system.h"
#include "entity_manager.h"
#include "component.h"
#include "entity.h"
#include "health_component.h"
#include "attack_component.h"
#include "defense_component.h"
#include "position_component.h"
#include "player_race_component.h"
#include "display_component.h"
#include "enemy_type_component.h"
#include "hostile_component.h"
#include "moveable_component.h"
#include "gold_component.h"
#include "enemy_has_compass_component.h"
#include "potion_type_component.h"
#include "treasure_component.h"
#include "can_pickup_component.h"
#include "item_type_component.h"
#include "compass_component.h"
#include "barrier_suit_component.h"
#include "stairs_component.h"

void SpawnSystem::spawnPlayer(EntityManager &entityManager, int x, int y, const std::string &race)
{
    auto player = entityManager.createEntity();

    if (race == "human")
    {
        player->addComponent(std::make_shared<HealthComponent>(140, 140));
        player->addComponent(std::make_shared<AttackComponent>(20));
        player->addComponent(std::make_shared<DefenseComponent>(20));
    }
    else if (race == "dwarf")
    {
        player->addComponent(std::make_shared<HealthComponent>(100, 100));
        player->addComponent(std::make_shared<AttackComponent>(20));
        player->addComponent(std::make_shared<DefenseComponent>(30));
    }
    else if (race == "elf")
    {
        player->addComponent(std::make_shared<HealthComponent>(140, 140));
        player->addComponent(std::make_shared<AttackComponent>(30));
        player->addComponent(std::make_shared<DefenseComponent>(10));
    }
    else if (race == "orc")
    {
        player->addComponent(std::make_shared<HealthComponent>(180, 180));
        player->addComponent(std::make_shared<AttackComponent>(30));
        player->addComponent(std::make_shared<DefenseComponent>(25));
    }

    player->addComponent(std::make_shared<DisplayComponent>('@'));
    player->addComponent(std::make_shared<PositionComponent>(x, y));
    player->addComponent(std::make_shared<PlayerRaceComponent>(race));
    player->addComponent(std::make_shared<GoldComponent>(0));
}

void SpawnSystem::spawnEnemy(EntityManager &entityManager, int x, int y, const std::string &enemyType)
{
    // Refactor to move all common components out
    auto enemy = entityManager.createEntity();
    if (enemyType == "vampire")
    {
        enemy->addComponent(std::make_shared<DisplayComponent>('V'));
        enemy->addComponent(std::make_shared<HealthComponent>(50, 50));
        enemy->addComponent(std::make_shared<AttackComponent>(25));
        enemy->addComponent(std::make_shared<DefenseComponent>(25));
        enemy->addComponent(std::make_shared<HostileComponent>(true));
        enemy->addComponent(std::make_shared<GoldComponent>(1));
    }
    else if (enemyType == "werewolf")
    {
        enemy->addComponent(std::make_shared<DisplayComponent>('W'));
        enemy->addComponent(std::make_shared<HealthComponent>(120, 120));
        enemy->addComponent(std::make_shared<AttackComponent>(30));
        enemy->addComponent(std::make_shared<DefenseComponent>(5));
        enemy->addComponent(std::make_shared<GoldComponent>(1));
        enemy->addComponent(std::make_shared<HostileComponent>(true));
    }
    else if (enemyType == "troll")
    {
        enemy->addComponent(std::make_shared<DisplayComponent>('T'));
        enemy->addComponent(std::make_shared<HealthComponent>(120, 120));
        enemy->addComponent(std::make_shared<AttackComponent>(25));
        enemy->addComponent(std::make_shared<DefenseComponent>(15));
        enemy->addComponent(std::make_shared<HostileComponent>(true));
        enemy->addComponent(std::make_shared<GoldComponent>(1));
    }
    else if (enemyType == "goblin")
    {
        enemy->addComponent(std::make_shared<DisplayComponent>('N'));
        enemy->addComponent(std::make_shared<HealthComponent>(70, 70));
        enemy->addComponent(std::make_shared<AttackComponent>(5));
        enemy->addComponent(std::make_shared<DefenseComponent>(10));
        enemy->addComponent(std::make_shared<HostileComponent>(true));
        enemy->addComponent(std::make_shared<GoldComponent>(1));
    }
    else if (enemyType == "merchant")
    {
        enemy->addComponent(std::make_shared<DisplayComponent>('M'));
        enemy->addComponent(std::make_shared<HealthComponent>(30, 30));
        enemy->addComponent(std::make_shared<AttackComponent>(70));
        enemy->addComponent(std::make_shared<DefenseComponent>(5));
        enemy->addComponent(std::make_shared<HostileComponent>(false));
        enemy->addComponent(std::make_shared<GoldComponent>(0));
    }
    else if (enemyType == "dragon")
    {
        enemy->addComponent(std::make_shared<DisplayComponent>('D'));
        enemy->addComponent(std::make_shared<HealthComponent>(150, 150));
        enemy->addComponent(std::make_shared<AttackComponent>(20));
        enemy->addComponent(std::make_shared<DefenseComponent>(20));
        enemy->addComponent(std::make_shared<HostileComponent>(true));
        enemy->addComponent(std::make_shared<GoldComponent>(0));
    }
    else if (enemyType == "phoenix")
    {
        enemy->addComponent(std::make_shared<DisplayComponent>('P'));
        enemy->addComponent(std::make_shared<HealthComponent>(50, 50));
        enemy->addComponent(std::make_shared<AttackComponent>(35));
        enemy->addComponent(std::make_shared<DefenseComponent>(20));
        enemy->addComponent(std::make_shared<HostileComponent>(true));
        enemy->addComponent(std::make_shared<GoldComponent>(1));
    }
    // Add more enemy types as needed
    enemy->addComponent(std::make_shared<EnemyHasCompassComponent>(false));
    enemy->addComponent(std::make_shared<MoveableComponent>(true));
    enemy->addComponent(std::make_shared<EnemyTypeComponent>(enemyType));
    enemy->addComponent(std::make_shared<PositionComponent>(x, y));
}

void SpawnSystem::spawnPotion(EntityManager &entityManager, int x, int y, const std::string &potionType)
{

    auto potion = entityManager.createEntity();
    potion->addComponent(std::make_shared<ItemTypeComponent>("potion"));
    potion->addComponent(std::make_shared<PositionComponent>(x, y));
    potion->addComponent(std::make_shared<DisplayComponent>('P'));
    potion->addComponent(std::make_shared<PotionTypeComponent>(potionType));
    potion->addComponent(std::make_shared<CanPickupComponent>(true));
}

void SpawnSystem::spawnTreasure(EntityManager &entityManager, int x, int y, const int &value)
{
    auto treasure = entityManager.createEntity();
    treasure->addComponent(std::make_shared<ItemTypeComponent>("treasure"));
    treasure->addComponent(std::make_shared<PositionComponent>(x, y));
    treasure->addComponent(std::make_shared<DisplayComponent>('G'));
    treasure->addComponent(std::make_shared<TreasureComponent>(value));

    if (value == 6) // Dragon hoard
    {
        treasure->addComponent(std::make_shared<CanPickupComponent>(false));
    }
    else
    {
        treasure->addComponent(std::make_shared<CanPickupComponent>(true));
    }
}

void SpawnSystem::spawnItem(EntityManager &entityManager, int x, int y, const std::string &itemType)
{
    auto item = entityManager.createEntity();
    item->addComponent(std::make_shared<PositionComponent>(x, y));
    item->addComponent(std::make_shared<ItemTypeComponent>(itemType));
    if (itemType == "compass")
    {
        item->addComponent(std::make_shared<DisplayComponent>('C'));
        item->addComponent(std::make_shared<CanPickupComponent>(true));
        item->addComponent(std::make_shared<CompassComponent>());
    }
    else if (itemType == "barrier_suit")
    {
        item->addComponent(std::make_shared<DisplayComponent>('B'));
        item->addComponent(std::make_shared<CanPickupComponent>(false));
        item->addComponent(std::make_shared<BarrierSuitComponent>());
    }
    else if (itemType == "stairs")
    {
        item->addComponent(std::make_shared<DisplayComponent>('\\'));
        item->addComponent(std::make_shared<CanPickupComponent>(false));
        item->addComponent(std::make_shared<StairsComponent>(false));
    }

    // Add more item types as needed
}