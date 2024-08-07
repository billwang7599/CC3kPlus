#ifndef DISPLAY_SYSTEM_H
#define DISPLAY_SYSTEM_H

#include <string>
#include <memory>
#include <iostream>
#include <iomanip>
#include <sstream>

using namespace std;

class EntityManager;
class Entity;

class DisplaySystem
{
    void outputColor(char c);

public:
    void update(EntityManager &entityManager, std::shared_ptr<Entity> player, int floor);
};

#endif