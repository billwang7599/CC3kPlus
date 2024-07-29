#include "combat_system.h"
#include "entity.h"
#include "entity_manager.h"
#include "attack_component.h"
#include "potion_effect_component.h"
#include "health_component.h"
#include "defense_component.h"
#include "lifesteal_component.h"
#include "goldsteal_component.h"
#include "gold_component.h"
#include "barrier_suit_component.h"
#include <cmath>
#include <algorithm>

using namespace std;

void CombatSystem::attack(Entity& attacker, Entity& defender) {
    // assumes we know who is attacking & defending
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

    // check for death ?

    if (health->current_health <= 0) {
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