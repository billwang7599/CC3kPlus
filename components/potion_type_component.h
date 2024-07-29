#include <string>

#include "component.h"

class PotionTypeComponent : public Component
{
public:
    std::string potion_type;
    PotionTypeComponent(std::string potion_type);
};