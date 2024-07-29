#include <iostream>
#include <memory>
#include <string>
#include "entities/entity_manager.h"
#include "systems/combat_system.h"
#include "systems/spawn_system.h"

using namespace std;

int main(int argc, char *argv[])
{
    // systems
    SpawnSystem spawn = SpawnSystem{};
    CombatSystem combat = CombatSystem{};

    // entity test
    EntityManager entitites = EntityManager{};
    spawn.spawnEnemy(entitites, 1, 0, "goblin");
    spawn.spawnPlayer(entitites, 0, 0, "human");
    shared_ptr<Entity> player = entitites.getEntity(0, 0);

    // combat test
    try {
        combat.battle(entitites, player, "ea");
        combat.battle(entitites, player, "ea");
        combat.battle(entitites, player, "ea");
    } catch (char const* e) {
        cout << e << '\n';
    }

    return 0;
}
