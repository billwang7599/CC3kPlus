#include <cmath>
#include <random>
#include <algorithm>
#include <iostream>
#include "systems/combat_system.h"
#include "entities/entity_manager.h"

using namespace std;

void CombatSystem::battle(EntityManager& entities, shared_ptr<Entity> player, const string& direction) {
    const int pCol = player->getComponent<PositionComponent>()->col;
    const int pRow = player->getComponent<PositionComponent>()->row;
    shared_ptr<Entity> target;
    vector<shared_ptr<Entity>> enemies;

    if (direction == "no") {
        target = entities.getEntity(pCol, pRow + 1);

    } else if (direction == "ea") {
        target = entities.getEntity(pCol + 1, pRow);

    }  else if (direction == "so") {
        target = entities.getEntity(pCol, pRow - 1);

    }  else if (direction == "we") {
        target = entities.getEntity(pCol - 1, pRow);

    }  else if (direction == "ne") {
        target = entities.getEntity(pCol + 1, pRow + 1);

    }  else if (direction == "nw") {
        target = entities.getEntity(pCol - 1, pRow + 1);

    }  else if (direction == "se") {
        target = entities.getEntity(pCol + 1, pRow - 1);

    }  else if (direction == "sw") {
        target = entities.getEntity(pCol - 1, pRow - 1);

    } else {
        throw "Not a valid direction!";
    }

    if (!target) {
        throw "No target there!";
    }

    cout << "Player is attacking the enemy" << '\n';
    attack(*player, *target);

    if (checkDeath(*target)) {
        if (target->getComponent<GoldComponent>()) {
            player->getComponent<GoldComponent>()->gold += target->getComponent<GoldComponent>()->gold;
        }
        entities.removeEntity(target);
    };

    // gang attack
    if (target) {
        random_device rd;
        mt19937 gen(rd());
        uniform_int_distribution<> distrib(0, 1);
        int result = distrib(gen);
        if (result == 0) {
            cout << "Enemy is attacking the player" << '\n';
            attack(*target, *player);
        }
    }
}

bool CombatSystem::checkDeath(Entity& e) {
    auto health = e.getComponent<HealthComponent>();
    return health->current_health <= 0;
}

void CombatSystem::attack(Entity& attacker, Entity& defender) {
    // assumes we know who is attacking & defending
    // check if they have component before accessing
    int attack, potion_attack = 0, defense, potion_defense = 0, damage;
    const auto potion_A = attacker.getComponent<PotionEffectComponent>();
    const auto potion_D = defender.getComponent<PotionEffectComponent>();
    int& health = defender.getComponent<HealthComponent>()->current_health;

    if (potion_A) {
        potion_attack = potion_A->attack_change;
    }
    if (potion_D) {
        defense = potion_D->defense_change;
    }


    attack = attacker.getComponent<AttackComponent>()->attack_power;
    defense = defender.getComponent<DefenseComponent>()->defense_power;
    damage = ceil((100.0)/(100 + defense + potion_defense)) * (attack + potion_attack);

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

    health -= damage;
    cout << damage << " damage done!" << '\n';
}

void CombatSystem::goldsteal(Entity& attacker, Entity& target) {
    // if the target doesn't have any gold, return
    if (!target.getComponent<GoldComponent>()) {
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