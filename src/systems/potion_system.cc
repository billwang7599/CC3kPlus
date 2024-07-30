#include "systems/potion_system.h"
#include "entities/entity_manager.h"
#include "entities/entity.h"
#include "components/components.h"

void PotionSystem::usePotion(EntityManager &entityManager, std::shared_ptr<Entity> player, std::shared_ptr<Entity> potion)
{
    std::string &potionType = potion->getComponent<PotionTypeComponent>()->potion_type;
    auto healthComponent = player->getComponent<HealthComponent>();
    auto potionEffectComponent = player->getComponent<PotionEffectComponent>();

    if (potionType == "RH")
    {
        healthComponent->currentHealth += 10;
        if (healthComponent->currentHealth > healthComponent->maxHealth)
        {
            healthComponent->currentHealth = healthComponent->maxHealth;
        }
    }
    else if (potionType == "BA")
    {
        potionEffectComponent->attackChange += 5;
    }
    else if (potionType == "BD")
    {
        potionEffectComponent->defenseChange += 5;
    }
    else if (potionType == "PH")
    {
        healthComponent->currentHealth -= 10;
    }
    else if (potionType == "WA")
    {
        potionEffectComponent->attackChange -= 5;
        if (potionEffectComponent->attackChange < 0)
        {
            potionEffectComponent->attackChange = 0;
        }
    }
    else if (potionType == "WD")
    {
        potionEffectComponent->defenseChange -= 5;
        if (potionEffectComponent->defenseChange < 0)
        {
            potionEffectComponent->defenseChange = 0;
        }
    }
    entityManager.removeEntity(potion);
}

void PotionSystem::update(EntityManager &entityManager, std::shared_ptr<Entity> player)
{
    std::shared_ptr<ActionComponent> actionComponent = player->getComponent<ActionComponent>();
    if (actionComponent->use)
    {
        std::shared_ptr<PositionComponent> positionComponent = player->getComponent<PositionComponent>();
        std::shared_ptr<Entity> potion;

        std::string &direction = player->getComponent<DirectionComponent>()->direction;
        if (direction == "no")
        {
            potion = entityManager.getEntity(positionComponent->row - 1, positionComponent->col);
        }
        else if (direction == "so")
        {
            potion = entityManager.getEntity(positionComponent->row + 1, positionComponent->col);
        }
        else if (direction == "ea")
        {
            potion = entityManager.getEntity(positionComponent->row, positionComponent->col + 1);
        }
        else if (direction == "we")
        {
            potion = entityManager.getEntity(positionComponent->row, positionComponent->col - 1);
        }
        else if (direction == "ne")
        {
            potion = entityManager.getEntity(positionComponent->row - 1, positionComponent->col + 1);
        }
        else if (direction == "nw")
        {
            potion = entityManager.getEntity(positionComponent->row - 1, positionComponent->col - 1);
        }
        else if (direction == "se")
        {
            potion = entityManager.getEntity(positionComponent->row + 1, positionComponent->col + 1);
        }
        else if (direction == "sw")
        {
            potion = entityManager.getEntity(positionComponent->row + 1, positionComponent->col - 1);
        }

        if (!potion)
        {
            return;
        }

        if (potion->getComponent<PotionTypeComponent>())
        {
            return;
        }
        usePotion(entityManager, player, potion);
    }
}