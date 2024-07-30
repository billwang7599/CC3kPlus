#include <iostream>
#include <memory>
#include <fstream>
#include <string>
#include "entities/entity_manager.h"
#include "systems/combat_system.h"
#include "systems/spawn_system.h"
#include "systems/display_system.h"
#include "systems/input_system.h"
#include "systems/movement_system.h"
#include "constants/constants.h"

int main(int argc, char *argv[])
{
    int floor = 0;
    bool gameLoop = true;
    std::string filePath;
    int seed = 123;

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
    InputSystem inputSystem;
    MovementSystem movementSystem;

    // Setup
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
            // displaySystem.update(entityManager); // prints out floor
        }
    }

    // Game
    shared_ptr<Entity> player;
    for (auto e : entityManagers[floor].getEntities())
    {
        if (e->getComponent<PlayerRaceComponent>())
        {
            player = e;
            break;
        }
    }
    while (gameLoop)
    {
        try
        {
            // the order matters
            inputSystem.update(player);
            movementSystem.update(entityManagers[floor], player);
            combatSystem.update(entityManagers[floor], player);
        }
        catch (std::string e)
        {
            std::cout << e << '\n';
        }
        catch (char const *e)
        {
            std::cout << e << '\n';
        } catch (exception& e) {
            std::cout << "Exception: " << e.what() << '\n';
        }
        displaySystem.update(entityManagers[floor]);
    }

    return 0;
}
