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
#include "systems/potion_system.h"
#include "systems/item_system.h"
#include "constants/constants.h"
#include "globals/global.h"

void reset(std::vector<EntityManager> &entityManagers, SpawnSystem &spawnSystem, int &seed, std::string &filePath, int &floor)
{
    floor = 0;
    for (int i = 0; i < NUM_FLOORS; i++)
    {
        EntityManager &entityManager = entityManagers.at(i);
        entityManager.getEntities().clear();
    }

    std::cout << "What race would you like to play as? (h | e | d | o)" << std::endl;
    char race_char;
    std::cin >> race_char;

    while (race_char != 'h' && race_char != 'e' && race_char != 'd' && race_char != 'o')
    {
        std::cout << "Invalid race. Try again." << std::endl;
        std::cin >> race_char;
    }

    std::string race;
    if (race_char == 'h')
        race = "human";
    else if (race_char == 'e')
        race = "elf";
    else if (race_char == 'd')
        race = "dwarf";
    else if (race_char == 'o')
        race = "orc";

    if (!filePath.empty())
    {
        spawnSystem.readFloors(entityManagers, filePath, race);
    }
    else
    {
        int barrier_suit_floor = std::rand() % 5;
        for (int i = 0; i < NUM_FLOORS; i++)
        {
            EntityManager &entityManager = entityManagers.at(i);
            spawnSystem.newFloor(entityManager, seed * (i + i), i == barrier_suit_floor, race);
        }
    }
}

std::shared_ptr<Entity> getPlayer(EntityManager &entityManager)
{
    for (auto &entity : entityManager.getEntities())
    {
        if (entity->getComponent<PlayerRaceComponent>())
        {
            return entity;
        }
    }
    return nullptr;
}

int main(int argc, char *argv[])
{
    bool gameLoop = true;
    std::string filePath;
    int seed = 2123;
    std::srand(seed);

    if (argc > 1)
    {
        filePath = argv[1];
    }
    if (argc > 2)
    {
        seed = atoi(argv[2]);
        std::srand(seed);
    }

    SpawnSystem spawnSystem;
    CombatSystem combatSystem;
    DisplaySystem displaySystem;
    PotionSystem potionSystem;
    ItemSystem itemSystem;
    InputSystem inputSystem;
    MovementSystem movementSystem;

    // Setup
    int floor = 0;
    std::vector<EntityManager> entityManagers(NUM_FLOORS);
    reset(entityManagers, spawnSystem, seed, filePath, floor);

    // Game
    shared_ptr<Entity> player = getPlayer(entityManagers[floor]);

    displaySystem.update(entityManagers[floor], player, floor);
    actionMessage.clear();

    while (gameLoop)
    {
        string input, command;
        std::getline(cin, input);
        if (input.empty())
        {
            continue;
        }

        if (input == "r")
        {
            reset(entityManagers, spawnSystem, seed, filePath, floor);
            player = getPlayer(entityManagers[floor]);
            displaySystem.update(entityManagers[floor], player, floor);
            continue;
        }
        else if (input == "q")
        {
            gameLoop = false;
        }

        try
        {
            // the order matters
            inputSystem.update(input, player);
            potionSystem.update(entityManagers[floor], player);
            itemSystem.update(entityManagers[floor], player);
            spawnSystem.update(entityManagers, floor, player);
            movementSystem.update(entityManagers[floor], player);
            combatSystem.update(entityManagers[floor], player);
            displaySystem.update(entityManagers[floor], player, floor);
        }
        catch (std::string e)
        {
            std::cout << e << '\n';
        }
        catch (char const *e)
        {
            std::cout << e << '\n';
        }
        catch (exception &e)
        {
            std::cout << "Exception: " << e.what() << '\n';
        }
        actionMessage.clear();

        // Lost the game
        if (player->getComponent<HealthComponent>()->currentHealth <= 0)
        {
            std::cout << "You died!" << std::endl;
            std::cout << "Would you like to play again? (y/n)" << std::endl;
            char playAgain;
            std::cin >> playAgain;
            if (playAgain == 'y')
            {
                reset(entityManagers, spawnSystem, seed, filePath, floor);
                player = getPlayer(entityManagers[floor]);
                displaySystem.update(entityManagers[floor], player, floor);
            }
            else
            {
                gameLoop = false;
            }
        }

        // Won the game
        if (floor == NUM_FLOORS)
        {
            std::cout << "Congratulations! You have completed the game!" << std::endl;

            int score = player->getComponent<GoldComponent>()->gold;
            if (player->getComponent<PlayerRaceComponent>()->race == "human")
            {
                score *= 1.5;
            }
            std::cout << "Your score is: " << score << std::endl;

            std::cout << "Would you like to play again? (y/n)" << std::endl;
            char playAgain;
            std::cin >> playAgain;
            if (playAgain == 'y')
            {
                reset(entityManagers, spawnSystem, seed, filePath, floor);
                player = getPlayer(entityManagers[floor]);
                displaySystem.update(entityManagers[floor], player, floor);
            }
            else
            {
                gameLoop = false;
            }
        }
    }

    return 0;
}
