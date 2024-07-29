#include <cmath>
#include <random>
#include <algorithm>
#include <iostream>
#include "systems/combat_system.h"
#include "entities/entity.h"
#include "entities/entity_manager.h"

using namespace std;

void CombatSystem::battle(EntityManager& entities, shared_ptr<Entity> player, const string& direction) {
    const int pCol = player->getComponent<PositionComponent>()->col;
    const int pRow = player->getComponent<PositionComponent>()->row;
    shared_ptr<Entity> enemy;

    if (direction == "no") {
        enemy = entities.getEntity(pCol, pRow + 1);

    } else if (direction == "ea") {
        enemy = entities.getEntity(pCol + 1, pRow);

    }  else if (direction == "so") {
        enemy = entities.getEntity(pCol, pRow - 1);

    }  else if (direction == "we") {
        enemy = entities.getEntity(pCol - 1, pRow);

    }  else if (direction == "ne") {
        enemy = entities.getEntity(pCol + 1, pRow + 1);

    }  else if (direction == "nw") {
        enemy = entities.getEntity(pCol - 1, pRow + 1);

    }  else if (direction == "se") {
        enemy = entities.getEntity(pCol + 1, pRow - 1);

    }  else if (direction == "sw") {
        enemy = entities.getEntity(pCol - 1, pRow - 1);

    } else {
        throw "Not a valid direction!";
    }

    if (!enemy) {
        throw "No enemy there!";
    }

    cout << "Player is attacking the enemy" << '\n';
    attack(*player, *enemy);
    if (checkDeath(*enemy)) {
        entities.removeEntity(enemy);
    };

    if (enemy) {
        random_device rd;
        mt19937 gen(rd());
        uniform_int_distribution<> distrib(0, 1);
        int result = distrib(gen);
        if (result == 0) {
            cout << "Enemy is attacking the player" << '\n';
            attack(*enemy, *player);
        }
    }

    // check game over?
}

bool CombatSystem::checkDeath(Entity& e) {
    auto health = e.getComponent<HealthComponent>();
    return health->current_health <= 0;
}

void CombatSystem::attack(Entity& attacker, Entity& defender) {
    // assumes we know who is attacking & defending
    // check if they have component before accessing
    const auto attack = attacker.getComponent<AttackComponent>();
    const auto potion_attack = attacker.getComponent<PotionEffectComponent>();

    const auto defense = defender.getComponent<DefenseComponent>();
    const auto potion_defense = defender.getComponent<PotionEffectComponent>();
    auto health = defender.getComponent<HealthComponent>();

    int damage = ceil((100)/(100 + defense->defense_power + potion_defense->defense_change)) * (attack->attack_power + potion_attack->attack_change);
    if (defender.getComponent<BarrierSuitComponent>() != nullptr) {
        damage = ceil(damage / 2);
    }

    // check for abilities
    if (attacker.getComponent<GoldStealComponent>()) {
        goldsteal(attacker, defender);
    }

    if (attacker.getComponent<LifestealComponent>()) {
        lifesteal(attacker, damage);
    }

    health->current_health -= damage;
    cout << damage << " damage done!" << '\n';

    if (checkDeath(defender)) {
        if (defender.getComponent<GoldComponent>()) {
            return;
        }
        attacker.getComponent<GoldComponent>()->gold += defender.getComponent<GoldComponent>()->gold;
    }
}

void CombatSystem::goldsteal(Entity& attacker, Entity& target) {
    // if the target doesn't have any gold, return
    if (target.getComponent<GoldComponent>()) {
        return;
    }

    // get either the stolen amount, or what the target has left
    int amount = min(attacker.getComponent<GoldStealComponent>()->amountStolen, target.getComponent<GoldComponent>()->gold);
    attacker.getComponent<GoldComponent>()->gold += amount;
    target.getComponent<GoldComponent>()->gold -= amount;
}

void CombatSystem::lifesteal(Entity& attacker, int damage) {
    auto health = attacker.getComponent<HealthComponent>();
    const auto lifesteal = attacker.getComponent<LifestealComponent>();
    health->current_health = min(health->max_health, int(health->current_health + damage * lifesteal->percentageStolen));
}