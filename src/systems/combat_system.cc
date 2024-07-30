#include <cmath>
#include <random>
#include <algorithm>
#include <iostream>
#include "systems/combat_system.h"
#include "entities/entity_manager.h"

using namespace std;

void CombatSystem::battle(EntityManager &entities, shared_ptr<Entity> player, const string &direction)
{
    const int pCol = player->getComponent<PositionComponent>()->col;
    const int pRow = player->getComponent<PositionComponent>()->row;
    shared_ptr<Entity> target;

    // Get target
    if (direction == "no")
    {
        target = entities.getEntity(pCol, pRow + 1);
    }
    else if (direction == "ea")
    {
        target = entities.getEntity(pCol + 1, pRow);
    }
    else if (direction == "so")
    {
        target = entities.getEntity(pCol, pRow - 1);
    }
    else if (direction == "we")
    {
        target = entities.getEntity(pCol - 1, pRow);
    }
    else if (direction == "ne")
    {
        target = entities.getEntity(pCol + 1, pRow + 1);
    }
    else if (direction == "nw")
    {
        target = entities.getEntity(pCol - 1, pRow + 1);
    }
    else if (direction == "se")
    {
        target = entities.getEntity(pCol + 1, pRow - 1);
    }
    else if (direction == "sw")
    {
        target = entities.getEntity(pCol - 1, pRow - 1);
    }
    else
    {
        throw "Not a valid direction!";
    }

    if (!target)
    {
        std::cout << "No target there!" << '\n';
    }
    else
    {
        std::cout << "Player is attacking the enemy" << '\n';
        attack(*player, *target);

        // check if target died
        if (checkDeath(*target))
        {
            if (target->getComponent<GoldComponent>())
            {
                player->getComponent<GoldComponent>()->gold += target->getComponent<GoldComponent>()->gold;
            }
            entities.removeEntity(target);
        };
    }

    enemies_attack(entities, *player);
    std::cout << '\n';
}

void CombatSystem::enemies_attack(EntityManager &entities, Entity &player)
{
    const int pCol = player.getComponent<PositionComponent>()->col;
    const int pRow = player.getComponent<PositionComponent>()->row;
    vector<shared_ptr<Entity>> enemies;

    for (int i = -1; i <= 1; i++)
    {
        for (int j = -1; j <= 1; j++)
        {
            if (i == j && i == 0)
            {
                continue;
            }
            enemies.push_back(entities.getEntity(pCol + i, pRow + j));
        }
    }

    for (auto &enemy : enemies)
    {
        if (!enemy)
        {
            continue;
        }
        random_device rd;
        mt19937 gen(rd());
        uniform_int_distribution<> distrib(0, 1);
        int result = distrib(gen);
        if (result == 0)
        {
            std::cout << "Enemy is attacking the player" << '\n';
            attack(*enemy, player);
        }
        enemy->getComponent<MoveableComponent>()->moveable = false;
    }
}

bool CombatSystem::checkDeath(Entity &e)
{
    auto health = e.getComponent<HealthComponent>();
    return health->currentHealth <= 0;
}

void CombatSystem::attack(Entity &attacker, Entity &defender)
{
    // assumes we know who is attacking & defending
    // check if they have component before accessing
    const auto attackerPotionEffect = attacker.getComponent<PotionEffectComponent>();
    const auto defenderPotionEffect = defender.getComponent<PotionEffectComponent>();

    int &health = defender.getComponent<HealthComponent>()->currentHealth;

    int attack = attacker.getComponent<AttackComponent>()->attackPower;
    int defense = defender.getComponent<DefenseComponent>()->defensePower;

    if (attackerPotionEffect)
    {
        attack += attackerPotionEffect->attackChange;
    }
    if (defenderPotionEffect)
    {
        defense += defenderPotionEffect->defenseChange;
    }

    int damage = ceil((100.0) / (100 + defense)) * (attack);

    if (defender.getComponent<BarrierSuitComponent>())
    {
        damage = ceil(damage / 2);
    }

    // check for abilities
    if (attacker.getComponent<GoldStealComponent>())
    {
        goldsteal(attacker, defender);
    }

    if (attacker.getComponent<LifestealComponent>())
    {
        lifesteal(attacker, damage);
    }

    health -= damage;
    std::cout << damage << " damage done!" << '\n';
}

void CombatSystem::goldsteal(Entity &attacker, Entity &target)
{
    // if the target doesn't have any gold, return
    if (!target.getComponent<GoldComponent>())
    {
        return;
    }

    // get either the stolen amount, or what the target has left
    int amount = min(attacker.getComponent<GoldStealComponent>()->amountStolen, target.getComponent<GoldComponent>()->gold);
    attacker.getComponent<GoldComponent>()->gold += amount;
    target.getComponent<GoldComponent>()->gold -= amount;
}

void CombatSystem::lifesteal(Entity &attacker, int damage)
{
    auto health = attacker.getComponent<HealthComponent>();
    const auto lifesteal = attacker.getComponent<LifestealComponent>();
    health->currentHealth = min(health->maxHealth, int(health->currentHealth + damage * lifesteal->percentageStolen));
}