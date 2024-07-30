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
    void spawnDragonAround(EntityManager &entityManager, int row, int col);
    void moveToNextFloor(std::vector<EntityManager> &entityManagers, int &floor, std::shared_ptr<Entity> player);

public:
    void readFloors(std::vector<EntityManager> &entityManagers, const std::string &filePath);
    void newFloor(EntityManager &entityManager, const int seed, bool spawnBarrierSuit);
    void spawnPlayer(EntityManager &entityManager, int x, int y, const std::string &race);
    void spawnEnemy(EntityManager &entityManager, int x, int y, const std::string &enemyType, bool withCompass);
    void spawnPotion(EntityManager &entityManager, int x, int y, const std::string &potionType);
    void spawnTreasure(EntityManager &entityManager, int x, int y, const int &value);
    void spawnItem(EntityManager &entityManager, int x, int y, const std::string &itemType);
    void update(std::vector<EntityManager> &entityManagers, int &floor, std::shared_ptr<Entity> player);
};

#endif