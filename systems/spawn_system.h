#include <memory>
#include <vector>
#include <string>
#include "entity_manager.h"
#include "component.h"
#include "entity.h"

class SpawnSystem
{
public:
    void spawnPlayer(EntityManager &entityManager, int x, int y, const std::string &race)
    {
        auto player = entityManager.createEntity();
        // player->addComponent(std::make_shared<HealthComponent>(attributes.maxHP, attributes.maxHP));
        // player->addComponent(std::make_shared<AttackComponent>(attributes.attackPower));
        // player->addComponent(std::make_shared<DefenseComponent>(attributes.defenseValue));
        // player->addComponent(std::make_shared<PositionComponent>(x, y));
        // player->addComponent(std::make_shared<RaceComponent>("Player", attributes));
        // player->addComponent(std::make_shared<GoldComponent>(0));
    }

    void spawnEnemy(EntityManager &entityManager, int x, int y, const std::string &enemyType)
    {
        auto enemy = entityManager.createEntity();
        if (enemyType == "Goblin")
        {
            // enemy->addComponent(std::make_shared<HealthComponent>(50, 50));
            // enemy->addComponent(std::make_shared<AttackComponent>(10));
            // enemy->addComponent(std::make_shared<DefenseComponent>(5));
            // enemy->addComponent(std::make_shared<PositionComponent>(x, y));
            // enemy->addComponent(std::make_shared<EnemyTypeComponent>("Goblin", 0));
        }
        else if (enemyType == "Dragon")
        {
            // enemy->addComponent(std::make_shared<HealthComponent>(150, 150));
            // enemy->addComponent(std::make_shared<AttackComponent>(20));
            // enemy->addComponent(std::make_shared<DefenseComponent>(15));
            // enemy->addComponent(std::make_shared<PositionComponent>(x, y));
            // enemy->addComponent(std::make_shared<EnemyTypeComponent>("Dragon", 0));
        }
        // Add more enemy types as needed
    }

    void spawnItem(EntityManager &entityManager, int x, int y, const std::string &itemType)
    {
        auto item = entityManager.createEntity();
        item->addComponent(std::make_shared<PositionComponent>(x, y));
        if (itemType == "Gold")
        {
            // item->addComponent(std::make_shared<ItemTypeComponent>("Gold", 1));
            // item->addComponent(std::make_shared<GoldComponent>(1));
        }
        else if (itemType == "Potion")
        {
            // item->addComponent(std::make_shared<ItemTypeComponent>("Potion", 1));
        }
        // Add more item types as needed
    }

    void spawnDragonAndHoard(EntityManager &entityManager, int chamberX, int chamberY)
    {
        // Get positions for hoard and dragon and spawn them together
    }
};
