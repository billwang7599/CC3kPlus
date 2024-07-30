#include "systems/display_system.h"
#include "constants/constants.h"
#include "constants/colours.h"
#include "entities/entity.h"
#include "entities/entity_manager.h"
#include "components/components.h"

void DisplaySystem::outputColor(char c)
{
    if (c == '|' || c == '-' || c == '+' || c == '#' || c == ' ')
        std::cout << MAG;
    else if (c == '.')
        std::cout << MAG;
    else if (c == 'G')
        std::cout << BHYEL;
    else if (c == '@' || c == '\\')
        std::cout << BHGRN;
    else if (c == 'P')
        std::cout << BHCYN;
    else if (c == 'V' || c == 'W' || c == 'N' || c == 'M' || c == 'D' || c == 'X' || c == 'T')
        std::cout << BHRED;
    std::cout << c << COLOR_RESET;
}

void DisplaySystem::update(EntityManager &entityManager, std::shared_ptr<Entity> player, int floor, std::string &action)
{
    if (player->getComponent<CompassComponent>())
    {
        std::cout << "Lol i have compass";
    }
    for (int row = 0; row < BOARD.size(); row++)
    {
        for (int col = 0; col < BOARD.at(row).size(); col++)
        {
            std::shared_ptr<Entity> entity = entityManager.getEntity(row, col);
            if (entity)
            {
                std::shared_ptr<DisplayComponent> displayComponent = entity->getComponent<DisplayComponent>();

                auto stairsComponent = entity->getComponent<StairsComponent>();

                if (stairsComponent && !player->getComponent<CompassComponent>())
                {
                    outputColor(BOARD.at(row).at(col));
                }
                else
                {
                    outputColor(displayComponent->display_char);
                }
            }
            else
            {
                outputColor(BOARD.at(row).at(col));
            }
        }
        std::cout << std::endl;
    }
    std::string output = "";
    output += "Race: " + player->getComponent<PlayerRaceComponent>()->race;
    output += " Gold: " + std::to_string(player->getComponent<GoldComponent>()->gold);
    output += " Floor: " + std::to_string(floor + 1);

    std::string attack_output = std::to_string(player->getComponent<AttackComponent>()->attackPower);
    std::string defense_output = std::to_string(player->getComponent<DefenseComponent>()->defensePower);

    auto potionEffectComponent = player->getComponent<PotionEffectComponent>();
    if (potionEffectComponent)
    {
        attack_output += " + " + std::to_string(potionEffectComponent->attackChange);
        defense_output += " + " + std::to_string(potionEffectComponent->defenseChange);
    }

    std::cout << output << std::endl;
    std::cout << "HP: " << player->getComponent<HealthComponent>()->currentHealth << std::endl;
    std::cout << "Atk: " << attack_output << std::endl;
    std::cout << "Def: " << defense_output << std::endl;
    std::cout << "Action: " << action << std::endl;
}
