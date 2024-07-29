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
#include "constants.h"

void SpawnSystem::newFloor(EntityManager &entityManager, const int seed = 10000)
{
    // Seed random number generator
    std::srand(seed);

    // Remove all entities from the previous floor except the player
    std::shared_ptr<Entity> player;
    for (auto &entity : entityManager.getEntities())
    {
        if (entity->getComponent<PlayerRaceComponent>())
        {
            player = entity;
            continue;
        }
        entityManager.removeEntity(entity);
    }

    // Spawn player in random room
    int playerRoom = std::rand() % 5;
    std::pair<int, int> playerPos = ROOMS[playerRoom][std::rand() % ROOMS[playerRoom].size()];
    player->getComponent<PositionComponent>()->row = playerPos.first;
    player->getComponent<PositionComponent>()->col = playerPos.second;

    // Spawn stairs in random room
    int stairsRoom = std::rand() % 5;
    while (stairsRoom == playerRoom)
    {
        stairsRoom = std::rand() % 5;
    }
    std::pair<int, int> stairsPos = ROOMS[stairsRoom][std::rand() % ROOMS[stairsRoom].size()];
    spawnItem(entityManager, stairsPos.first, stairsPos.second, "stairs");

    // Spawn 10 potions
    int potionsToSpawn = 10;
    std::vector<std::string> potionTypes = {"RH", "BA", "BD", "PH", "WA", "WD"};
    while (potionsToSpawn > 0)
    {
        std::string potionType = potionTypes[std::rand() % 6];
        int potionRoom = std::rand() % 5;
        std::pair<int, int> potionPos = ROOMS[potionRoom][std::rand() % ROOMS[potionRoom].size()];

        while (entityManager.getEntity(potionPos.first, potionPos.second)) // No collision
        {
            potionRoom = std::rand() % 5;
            potionPos = ROOMS[potionRoom][std::rand() % ROOMS[potionRoom].size()];
        }

        spawnPotion(entityManager, potionPos.first, potionPos.second, potionType);
        potionsToSpawn--;
    }

    // Spawn 10 treasures
    int treasureToSpawn = 10;
    int enemiesToSpawn = 20; // if a dragon is spawned, decrement
    while (treasureToSpawn > 0)
    {
        int treasureRoom = std::rand() % 5;
        std::vector<std::pair<int, int>> treasureRoomCoords = ROOMS[treasureRoom];
        std::pair<int, int> treasurePos = treasureRoomCoords[std::rand() % treasureRoomCoords.size()];

        while (entityManager.getEntity(treasurePos.first, treasurePos.second)) // No collision
        {
            treasureRoom = std::rand() % 5;
            treasurePos = treasureRoomCoords[std::rand() % treasureRoomCoords.size()];
        }

        // Determine type of treasure to spawn
        int treasureTypeRoll = std::rand() % 8; // Random number between 0 and 7
        int treasureValue;
        if (treasureTypeRoll < 5) // 5/8 chance
        {
            treasureValue = 1;
        }
        else if (treasureTypeRoll == 5) // 1/8 chance
        {
            treasureValue = 6;
        }
        else // 2/8 chance (1/4)
        {
            treasureValue = 2;
        }

        spawnTreasure(entityManager, treasurePos.first, treasurePos.second, treasureValue);
        if (treasureValue == 6) // Spawn dragon
        {
            for (int i = -1; i <= 1; i++)
            {
                for (int j = -1; j <= 1; j++)
                {
                    if (i == 0 && j == 0)
                    {
                        continue;
                    }
                    std::pair<int, int> dragonPos = std::make_pair(treasurePos.first + i, treasurePos.second + j);

                    if (entityManager.getEntity(dragonPos.first, dragonPos.second))
                    {
                        continue;
                    }
                    if (BOARD[dragonPos.first][dragonPos.second] != '.') // if dragonPos is not a floor tile
                    {
                        continue;
                    }
                    spawnEnemy(entityManager, treasurePos.first + i, treasurePos.second + j, "dragon");
                    enemiesToSpawn--;
                    break;
                }
            }
        };
        treasureToSpawn--;
    }

    // Spawn 20 enemies
    while (enemiesToSpawn > 0)
    {
        int enemyRoom = std::rand() % 5;
        std::pair<int, int> enemyPos = ROOMS[enemyRoom][std::rand() % ROOMS[enemyRoom].size()];

        while (entityManager.getEntity(enemyPos.first, enemyPos.second)) // No collision
        {
            enemyRoom = std::rand() % 5;
            enemyPos = ROOMS[enemyRoom][std::rand() % ROOMS[enemyRoom].size()];
        }

        int enemyTypeRoll = std::rand() % 18;
        std::string enemyType;
        if (enemyTypeRoll < 4) // 4/18 = 2/9 chance
        {
            enemyType = "werewolf";
        }
        else if (enemyTypeRoll < 7) // 3/18 chance
        {
            enemyType = "vampire";
        }
        else if (enemyTypeRoll < 12) // 5/18 chance
        {
            enemyType = "goblin";
        }
        else if (enemyTypeRoll < 14) // 1/9 chance
        {
            enemyType = "troll";
        }
        else if (enemyTypeRoll < 16) // 1/9 chance
        {
            enemyType = "phoenix";
        }
        else if (enemyTypeRoll < 18) // 1/9 chance
        {
            enemyType = "merchant";
        }

        spawnEnemy(entityManager, enemyPos.first, enemyPos.second, enemyType);
        enemiesToSpawn--;
    }
}

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