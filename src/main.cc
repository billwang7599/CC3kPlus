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
    int seed = 0;

    if (argc > 1)
    {
        filePath = argv[1];
    }
    if (argc > 2)
    {
        seed = atoi(argv[2]);
        std::srand(seed);
    }

    std::vector<EntityManager> entityManagers{5};
    if (!filePath.empty())
    {
        // load game
    }
    else
    {
        for (int i = 0; i < 5; i++)
        {
            entityManagers.push_back(EntityManager());
        }
    }

    int currentFloor = 0;
    EntityManager entityManager = entityManagers.at(currentFloor);

    SpawnSystem spawnSystem;
    CombatSystem combatSystem;
    DisplaySystem displaySystem;

    if (!filePath.empty())
    {
        // load game
    }
    else
    {
        spawnSystem.newFloor(entityManager, seed);
    }

    spawnSystem.spawnPlayer(entityManager, 3, 3, "human");
    spawnSystem.newFloor(entityManager, 0);

    while (true)
    {
        displaySystem.update(entityManager);
        break;
    }

    return 0;
}
