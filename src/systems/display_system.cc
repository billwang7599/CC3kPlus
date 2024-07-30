#include "systems/display_system.h"
#include "constants/constants.h"
#include "constants/colours.h"
#include "entities/entity_manager.h"
#include "components/display_component.h"
#include "components/stairs_component.h"

void DisplaySystem::outputColor(char c)
{
    if (c == '|' || c == '-' || c == '+' || c == '#' || c == ' ')
        std::cout << MAG;
    else if (c == '.')
        std::cout << MAG;
    else if (c == 'G')
        std::cout << BHYEL;
    else if (c == '@')
        std::cout << BHGRN;
    else if (c == 'P')
        std::cout << BHCYN;
    else if (c == 'V' || c == 'W' || c == 'N' || c == 'M' || c == 'D' || c == 'X' || c == 'T')
        std::cout << BHRED;
    std::cout << c << COLOR_RESET;
}

void DisplaySystem::update(EntityManager &entityManager)
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
                if (stairsComponent && !stairsComponent->visible)
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
}