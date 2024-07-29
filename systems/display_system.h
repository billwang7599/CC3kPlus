#ifndef DISPLAY_SYSTEM_H
#define DISPLAY_SYSTEM_H

#include <string>
#include <memory>
#include <iostream>

using namespace std;

class EntityManager;

class DisplaySystem
{
public:
    void update(EntityManager &);
};

#endif