#ifndef SPAWN_SYSTEM_H
#define SPAWN_SYSTEM_H

#include <memory>
#include <vector>
#include <string>
#include <cstdlib>
#include <algorithm>
#include <utility>
#include <fstream>
#include <iostream>

class EntityManager;
class Entity;
class SpawnSystem
{
    std::shared_ptr<Entity> spawnDragonAround(EntityManager &entityManager, int row, int col);

public:
    void readFloors(std::vector<EntityManager> &entityManagers, const std::string &filePath);
    void newFloor(EntityManager &entityManager, const int seed, bool spawn_barrier_suit);
    std::shared_ptr<Entity> spawnPlayer(EntityManager &entityManager, int x, int y, const std::string &race);
    std::shared_ptr<Entity> spawnEnemy(EntityManager &entityManager, int x, int y, const std::string &enemyType);
    std::shared_ptr<Entity> spawnPotion(EntityManager &entityManager, int x, int y, const std::string &potionType);
    std::shared_ptr<Entity> spawnTreasure(EntityManager &entityManager, int x, int y, const int &value);
    std::shared_ptr<Entity> spawnItem(EntityManager &entityManager, int x, int y, const std::string &itemType);
};

#endif