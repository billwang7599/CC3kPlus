#include <iostream>
#include "entity_manager.h"
#include "combat_system.h"
#include "spawn_system.h"
#include "display_system.h"

#include "attack_component.h"
#include "defense_component.h"
#include "health_component.h"
#include "position_component.h"
#include "player_race_component.h"
#include "gold_component.h"
#include "display_component.h"

using namespace std;

int main(int argc, char *argv[])
{
    // systems
    EntityManager entityManager;
    SpawnSystem spawnSystem;
    CombatSystem combatSystem;
    DisplaySystem displaySystem;

    // entity test
    // shared_ptr<Entity> player = entityManager.createEntity();
    // spawn.spawnEnemy(entitites, 1, 1, "goblin");
    // spawn.spawnPlayer(entitites, 0, 1, "human");
    // shared_ptr<Entity> player = entitites.getEntity(0, 1);

    // // combat test
    // combat.battle(entitites, player, "ea");
    // combat.battle(entitites, player, "ea");
    // combat.battle(entitites, player, "ea");

    spawnSystem.spawnPlayer(entityManager, 4, 4, "human");
    spawnSystem.newFloor(entityManager, 10000);

    displaySystem.update(entityManager);

    return 0;
}
