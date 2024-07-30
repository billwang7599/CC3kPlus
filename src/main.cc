#include <iostream>
#include <memory>
#include <fstream>
#include <string>
#include "entities/entity_manager.h"
#include "systems/combat_system.h"
#include "systems/spawn_system.h"
#include "systems/display_system.h"
#include "constants/constants.h"

int main(int argc, char *argv[])
{
    std::string filePath;
    int seed = 10000;

    if (argc > 1)
    {
        filePath = argv[1];
    }
    if (argc > 2)
    {
        seed = atoi(argv[2]);
    }
    std::srand(seed);

    SpawnSystem spawnSystem;
    CombatSystem combatSystem;
    DisplaySystem displaySystem;

    std::vector<EntityManager> entityManagers(NUM_FLOORS);
    if (!filePath.empty())
    {
        spawnSystem.readFloors(entityManagers, filePath);
    }
    else
    {
        int barrier_suit_floor = std::rand() % 5;
        for (int i = 0; i < NUM_FLOORS; i++)
        {
            EntityManager &entityManager = entityManagers.at(i);
            spawnSystem.newFloor(entityManager, seed * (i + i), i == barrier_suit_floor);
            displaySystem.update(entityManager);
        }
    }

    return 0;
}
