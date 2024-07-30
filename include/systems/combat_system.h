#ifndef COMBAT_SYSTEM_H
#define COMBAT_SYSTEM_H

#include <string>
#include <memory>

using namespace std;

class Entity;
class EntityManager;

class CombatSystem
{
    void lifesteal(Entity &, int);
    void goldsteal(Entity &, Entity &);
    void attack(Entity &, Entity &);
    bool checkDeath(Entity &);
    void enemies_attack(EntityManager &, Entity &);
    void battle(EntityManager &, shared_ptr<Entity>, const string &);

public:
    void update(EntityManager &, shared_ptr<Entity>);
};

#endif