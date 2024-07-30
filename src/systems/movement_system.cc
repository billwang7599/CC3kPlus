#include "systems/movement_system.h"
#include "constants/constants.h"
#include <utility>
#include <vector>
#include <algorithm>
#include <iostream>
#include <cmath>
#include "globals/global.h"

bool compare(std::shared_ptr<Entity> e0, std::shared_ptr<Entity> e1) {
    PositionComponent a = *e0->getComponent<PositionComponent>();
    PositionComponent b = *e1->getComponent<PositionComponent>();

    if (a.row != b.row) {
        return a.row < b.row; // Sort by y first
    }
    return a.col < b.col; // If y is the same, sort by x
}

void MovementSystem::update(EntityManager& entities, std::shared_ptr<Entity> player) {
    // set all enemy move to true
    for (auto &e : entities.getEntities())
    {
        if (e->getComponent<EnemyTypeComponent>())
        {
            e->getComponent<MoveableComponent>()->moveable = true;
        }
    }

    // player move
    if (player->getComponent<ActionComponent>()->move)
    {
        if (!moveEntity(entities, *player, player->getComponent<DirectionComponent>()->direction))
        {
            throw "Cannot move there!";
        };

        // check for potions
        const int pCol = player->getComponent<PositionComponent>()->col;
        const int pRow = player->getComponent<PositionComponent>()->row;
        for (int i = -1; i <= 1; i++) {
            for (int j = -1; j <= 1; j++)
            {
                if (i == j && i == 0)
                {
                    continue;
                }

                std::shared_ptr<Entity> e = entities.getEntity(pRow + i, pCol + j);
                if (!e || !e->getComponent<PotionTypeComponent>()) {
                    continue;
                }
                if (std::find(seenPotions.begin(), seenPotions.end(), e->getComponent<PotionTypeComponent>()->potion_type) != seenPotions.end()) {
                    // already seen
                    actionMessage.push_back("PC moves " + player->getComponent<DirectionComponent>()->direction +
                        " and sees a " + e->getComponent<PotionTypeComponent>()->potion_type + " potion.");
                } else {
                    actionMessage.push_back(
                        "PC moves " + player->getComponent<DirectionComponent>()->direction +
                        " and sees an unkown potion.");
                }
            }
        }
        if (actionMessage.size() == 0) {
            actionMessage.push_back("PC moves " + player->getComponent<DirectionComponent>()->direction + ".");
        }
    }

    freezeEnemies(entities, *player);

    std::vector<std::shared_ptr<Entity>> enemies;
    for (auto& e : entities.getEntities()) {
        if (!e->getComponent<EnemyTypeComponent>() || !e->getComponent<MoveableComponent>()->moveable) {
            continue;
        }
        enemies.push_back(e);
    }
    std::sort(enemies.begin(), enemies.end(), compare);
    for (auto& e : enemies) {
        moveEnemy(entities, *e);
    }

    freezeEnemies(entities, *player);
}

void MovementSystem::freezeEnemies(EntityManager &entities, Entity &player)
{
    const int pCol = player.getComponent<PositionComponent>()->col;
    const int pRow = player.getComponent<PositionComponent>()->row;
    std::shared_ptr<Entity> e;

    for (int i = -1; i <= 1; i++)
    {
        for (int j = -1; j <= 1; j++)
        {
            e = entities.getEntity(pRow + i, pCol + j);
            if ((i == j && i == 0) || !e || !e->getComponent<EnemyTypeComponent>())
            { // if entity is nullptr or i == j == 0
                continue;
            }
            e->getComponent<MoveableComponent>()->moveable = false;
        }
    }
}

void MovementSystem::moveEnemy(EntityManager &entities, Entity &enemy)
{
    auto it = DIRECTION_MAP.begin();
    std::advance(it, std::rand() % 8);
    std::string direction = it->first;
    while (!moveEntity(entities, enemy, direction))
    {
        it = DIRECTION_MAP.begin();
        advance(it, std::rand() % 8);
        direction = it->first;
    };
}

bool MovementSystem::moveEntity(EntityManager &entities, Entity &e, std::string &direction)
{
    // check map and entities
    int newRow = e.getComponent<PositionComponent>()->row + DIRECTION_MAP.at(direction).first;
    int newCol = e.getComponent<PositionComponent>()->col + DIRECTION_MAP.at(direction).second;
    if (entities.getEntity(newRow, newCol) || BOARD[newRow][newCol] == '|' || BOARD[newRow][newCol] == '-' || BOARD[newRow][newCol] == ' ')
    {
        return false;
    }

    // enemy checks
    if (e.getComponent<EnemyTypeComponent>() && BOARD[newRow][newCol] == '+')
    {
        return false;
    }
    if (e.getComponent<EnemyTypeComponent>() && e.getComponent<EnemyTypeComponent>()->enemy_type == "dragon")
    {
        std::shared_ptr<GuardingPositionComponent> guardCoords = e.getComponent<GuardingPositionComponent>();
        if (!guardCoords)
        {
            throw std::runtime_error("Dragon does not have guarding position component");
        }

        if (abs(guardCoords->col - newCol) > 1 || abs(guardCoords->row - newRow) > 1)
        {
            return false;
        }
    }
    e.getComponent<PositionComponent>()->col = newCol;
    e.getComponent<PositionComponent>()->row = newRow;
    return true;
}