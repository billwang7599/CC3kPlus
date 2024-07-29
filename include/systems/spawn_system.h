#ifndef SPAWN_SYSTEM_H
#define SPAWN_SYSTEM_H

#include <memory>
#include <vector>
#include <string>
#include <cstdlib>
#include <algorithm>
#include <utility>

class EntityManager;
class SpawnSystem
{
public:
    void newFloor(EntityManager &entityManager, const int seed);
    void spawnPlayer(EntityManager &entityManager, int x, int y, const std::string &race);
    void spawnEnemy(EntityManager &entityManager, int x, int y, const std::string &enemyType);
    void spawnPotion(EntityManager &entityManager, int x, int y, const std::string &potionType);
    void spawnTreasure(EntityManager &entityManager, int x, int y, const int &value);
    void spawnItem(EntityManager &entityManager, int x, int y, const std::string &itemType);
};

#endif