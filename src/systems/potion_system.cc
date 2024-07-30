#include "systems/potion_system.h"
#include "entities/entity_manager.h"
#include "entities/entity.h"
#include "components/components.h"
#include "globals/global.h"
#include "constants/constants.h"

void PotionSystem::usePotion(EntityManager &entityManager, std::shared_ptr<Entity> player, std::shared_ptr<Entity> potion)
{
    std::string potionType = potion->getComponent<PotionTypeComponent>()->potion_type;
    auto healthComponent = player->getComponent<HealthComponent>();
    auto potionEffectComponent = player->getComponent<PotionEffectComponent>();
    seenPotions.push_back(potionType);
    actionMessage += "PC uses " + potionType + ".\n";

    if (player->getComponent<AllPositiveComponent>()) {
        if (potionType == "PH")
        {
            potionType = "RH";
        }
        else if (potionType == "WA")
        {
            potionType = "BA";
        }
        else if (potionType == "WD")
        {
            potionType = "BD";
        }
    }

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
    if (!actionComponent->use)
        return;

    std::shared_ptr<PositionComponent> positionComponent = player->getComponent<PositionComponent>();
    std::string &direction = player->getComponent<DirectionComponent>()->direction;

    int row = positionComponent->row + DIRECTION_MAP.at(direction).first;
    int col = positionComponent->col + DIRECTION_MAP.at(direction).second;
    std::shared_ptr<Entity> potion = entityManager.getEntity(row, col);

    if (!potion)
    {
        return;
    }

    if (!potion->getComponent<PotionTypeComponent>())
    {
        return;
    }
    usePotion(entityManager, player, potion);
}