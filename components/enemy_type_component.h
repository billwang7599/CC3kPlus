#include <string>

#include "component.h"

class EnemyTypeComponent : public Component
{
public:
    std::string enemy_type;
    EnemyTypeComponent(std::string enemy_type);
};