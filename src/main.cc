#include <iostream>
#include "entity_manager.h"
#include "combat_system.h"
#include "spawn_system.h"

using namespace std;

int main(int argc, char *argv[])
{
    // systems
    SpawnSystem spawn = SpawnSystem{};
    CombatSystem combat = CombatSystem{};

    // entity test
    EntityManager entitites = EntityManager{};
    spawn.spawnEnemy(entitites, 1, 1, "goblin");
    spawn.spawnPlayer(entitites, 0, 1, "human");
    shared_ptr<Entity> player = entitites.getEntity(0, 1);

    // combat test
    combat.battle(entitites, player, "ea");
    combat.battle(entitites, player, "ea");
    combat.battle(entitites, player, "ea");

    return 0;
}
