#include "systems/display_system.h"
#include "constants/constants.h"
#include "constants/colours.h"
#include "entities/entity.h"
#include "entities/entity_manager.h"
#include "components/components.h"
#include "globals/global.h"

void DisplaySystem::outputColor(char c)
{
    if (c == '|' || c == '-' || c == '+' || c == '#' || c == ' ')
        std::cout << MAG;
    else if (c == '.')
        std::cout << MAG;
    else if (c == 'G')
        std::cout << BHYEL;
    else if (c == 'C' || c == 'B')
        std::cout << BHGRN;
    else if (c == '@' || c == '\\')
        std::cout << BHWHT;
    else if (c == 'P')
        std::cout << BHCYN;
    else if (c == 'V' || c == 'W' || c == 'N' || c == 'M' || c == 'D' || c == 'X' || c == 'T')
        std::cout << BHRED;
    std::cout << c << COLOR_RESET;
}

void DisplaySystem::update(EntityManager &entityManager, std::shared_ptr<Entity> player, int floor)
{
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

    // Format gold to 1 decimal place
    std::ostringstream goldStream;
    goldStream << std::fixed << std::setprecision(1) << player->getComponent<GoldComponent>()->gold;
    output += " Gold: " + goldStream.str();

    output += " Floor: " + std::to_string(floor + 1);

    // std::string attack_output = std::to_string(player->getComponent<AttackComponent>()->attackPower);
    // std::string defense_output = std::to_string(player->getComponent<DefenseComponent>()->defensePower);
    int attack_output = (player->getComponent<AttackComponent>()->attackPower);
    int defense_output = (player->getComponent<DefenseComponent>()->defensePower);

    auto potionEffectComponent = player->getComponent<PotionEffectComponent>();
    if (potionEffectComponent)
    {
        // attack_output += " + " + std::to_string(potionEffectComponent->attackChange);
        // defense_output += " + " + std::to_string(potionEffectComponent->defenseChange);
        attack_output += (potionEffectComponent->attackChange);
        defense_output += (potionEffectComponent->defenseChange);
    }

    std::cout << output << std::endl;
    std::cout << "HP: " << player->getComponent<HealthComponent>()->currentHealth << std::endl;
    std::cout << "Atk: " << attack_output << std::endl;
    std::cout << "Def: " << defense_output << std::endl;

    // process action
    std::cout << "Action: ";
    for (int i = 0; i < actionMessage.size(); i++) {
        actionMessage[i][0] = toupper(actionMessage[i][0]);
        std::cout << actionMessage[i];
        if (i != actionMessage.size() - 1) {
            std::cout << " ";
        }
    }
    std::cout << "\n";
}
