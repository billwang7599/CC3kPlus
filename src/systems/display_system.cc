#include "systems/display_system.h"
#include "constants/constants.h"
#include "entities/entity_manager.h"
#include "components/display_component.h"
#include "components/stairs_component.h"

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
                    std::cout << BOARD.at(row).at(col);
                }
                else
                {
                    std::cout << displayComponent->display_char;
                }
            }
            else
            {
                std::cout << BOARD.at(row).at(col);
            }
        }
        std::cout << std::endl;
    }
}