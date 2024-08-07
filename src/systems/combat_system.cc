#include <cmath>
#include <random>
#include <algorithm>
#include <iostream>
#include "systems/combat_system.h"
#include "entities/entity_manager.h"
#include "constants/constants.h"
#include "globals/global.h"
using namespace std;

void CombatSystem::update(EntityManager &entities, shared_ptr<Entity> player)
{
    if (player->getComponent<ActionComponent>()->attack)
    {
        battle(entities, player, player->getComponent<DirectionComponent>()->direction);
    }
    enemies_attack(entities, *player);
}

void CombatSystem::battle(EntityManager &entities, shared_ptr<Entity> player, const string &direction)
{
    const int pCol = player->getComponent<PositionComponent>()->col;
    const int pRow = player->getComponent<PositionComponent>()->row;
    shared_ptr<Entity> target;

    // Get target
    try
    {
        target = entities.getEntity(pRow + DIRECTION_MAP.at(direction).first, pCol + DIRECTION_MAP.at(direction).second);
    }
    catch (exception e)
    {
        throw "Not a valid direction!";
    }

    if (!target)
    {
        actionMessage.push_back("PC attacked " + direction + " but nothing was there...");
        return;
    }

    attack(*player, *target);

    // check if target died
    if (!checkDeath(*target))
    {
        return;
    }

    // if merchant, change him to a gold pile
    if (target->getComponent<EnemyTypeComponent>()->enemy_type == "merchant")
    {
        // if he is non hostile, change all merchants to hostile
        target->removeComponent<EnemyTypeComponent>();
        target->removeComponent<DisplayComponent>();
        target->addComponent(std::make_shared<DisplayComponent>('G'));
        target->addComponent(std::make_shared<TreasureComponent>(4));
        target->addComponent(std::make_shared<ItemTypeComponent>("treasure"));
        target->addComponent(std::make_shared<CanPickupComponent>());
        return;
    }

    // if dragon, then make the treasure it's guarding pick uppable
    if (target->getComponent<EnemyTypeComponent>()->enemy_type == "dragon")
    {
        std::shared_ptr<GuardingPositionComponent> pos = target->getComponent<GuardingPositionComponent>();
        std::shared_ptr<Entity> treasure = entities.getEntity(pos->row, pos->col);
        treasure->addComponent(std::make_shared<CanPickupComponent>());
    }

    // if enemy holds compass, turn him into the compass
    if (target->getComponent<CompassComponent>())
    {
        target->removeComponent<EnemyTypeComponent>();
        target->removeComponent<DisplayComponent>();
        target->addComponent(std::make_shared<DisplayComponent>('C'));
        target->addComponent(std::make_shared<ItemTypeComponent>("compass"));
        target->addComponent(std::make_shared<CanPickupComponent>());
    }

    if (target->getComponent<GoldComponent>())
    {
        float gold = target->getComponent<GoldComponent>()->gold;
        if (player->getComponent<GoldMultiplierComponent>())
        {
            gold *= player->getComponent<GoldMultiplierComponent>()->percent;
        }
        player->getComponent<GoldComponent>()->gold += gold;
    }

    if (target->getComponent<EnemyTypeComponent>())
    {
        entities.removeEntity(target);
    }
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
            enemies.push_back(entities.getEntity(pRow + i, pCol + j));
        }
    }

    for (auto &enemy : enemies)
    {
        if (!enemy || !enemy->getComponent<EnemyTypeComponent>())
        {
            continue;
        }
        // if no merchant has died, continue
        if (enemy->getComponent<EnemyTypeComponent>()->enemy_type == "merchant" && !merchantHostile)
        {
            continue;
        }

        // if dragon, and not next to guard, continue
        if (enemy->getComponent<EnemyTypeComponent>()->enemy_type == "dragon")
        {
            std::shared_ptr<GuardingPositionComponent> pos = enemy->getComponent<GuardingPositionComponent>();
            if (abs(pCol - pos->col) > 1 || abs(pRow - pos->row) > 1)
            {
                continue;
            }
        }

        if (random() % 2 == 0)
        {
            attack(*enemy, player);
        }
        else
        {
            actionMessage.push_back(enemy->getComponent<EnemyTypeComponent>()->enemy_type + " missed the player!");
        }
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
    if (attacker.getComponent<PlayerRaceComponent>())
    {
        actionMessage.push_back("PC deals " + to_string(damage) + " to " +
                                defender.getComponent<EnemyTypeComponent>()->enemy_type + " (" + to_string(health) + " HP).");

        if (defender.getComponent<EnemyTypeComponent>()->enemy_type == "merchant")
        {
            merchantHostile = true;
        }
    }
    else
    {
        actionMessage.push_back(attacker.getComponent<EnemyTypeComponent>()->enemy_type + " deals " + to_string(damage) + " to PC.");
    }
}

void CombatSystem::goldsteal(Entity &attacker, Entity &target)
{
    // if the target doesn't have any gold, return
    if (!target.getComponent<GoldComponent>())
    {
        return;
    }

    // get either the stolen amount, or what the target has left
    float amount = min(attacker.getComponent<GoldStealComponent>()->amountStolen, target.getComponent<GoldComponent>()->gold);
    attacker.getComponent<GoldComponent>()->gold += amount;
    target.getComponent<GoldComponent>()->gold -= amount;
}

void CombatSystem::lifesteal(Entity &attacker, int damage)
{
    auto health = attacker.getComponent<HealthComponent>();
    const auto lifesteal = attacker.getComponent<LifestealComponent>();
    health->currentHealth = min(health->maxHealth, int(health->currentHealth + damage * lifesteal->percentageStolen));
}