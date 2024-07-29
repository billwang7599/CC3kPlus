#include "component.h"
#include <string>

class PotionTypeComponent : public Component
{
public:
    std::string potion_type;
    PotionTypeComponent(std::string potion_type) : potion_type{potion_type} {};
};
