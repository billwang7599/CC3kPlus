#include "component.h"
#include <string>

class EnemyTypeComponent : public Component
{
public:
    std::string enemy_type;
    EnemyTypeComponent(std::string enemy_type) : enemy_type{enemy_type} {};
};
