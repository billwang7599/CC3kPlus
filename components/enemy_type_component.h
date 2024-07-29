#ifndef ENEMY_TYPE_COMPONENT_H
#define ENEMY_TYPE_COMPONENT_H

#include <string>
#include "component.h"

class EnemyTypeComponent : public Component
{
public:
    std::string enemy_type;
    EnemyTypeComponent(std::string enemy_type) : enemy_type{enemy_type} {}
};

#endif