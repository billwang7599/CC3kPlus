#include "systems/movement_system.h"
#include "constants/constants.h"
#include <utility>
#include <vector>
#include <algorithm>
#include <iostream>
#include <cmath>

void MovementSystem::update(EntityManager &entities, std::shared_ptr<Entity> player)
{
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
    }

    freezeEnemies(entities, *player);

    for (auto &e : entities.getEntities())
    {
        if (!e->getComponent<EnemyTypeComponent>() || !e->getComponent<MoveableComponent>()->moveable)
        {
            continue;
        }
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
    auto it = directions.begin();
    std::advance(it, std::rand() % 8);
    std::string direction = it->first;
    while (!moveEntity(entities, enemy, direction))
    {
        it = directions.begin();
        advance(it, std::rand() % 8);
        direction = it->first;
    };
}

bool MovementSystem::moveEntity(EntityManager &entities, Entity &e, std::string &direction)
{
    // check map and entities
    int newRow = e.getComponent<PositionComponent>()->row + directions.at(direction).first;
    int newCol = e.getComponent<PositionComponent>()->col + directions.at(direction).second;
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