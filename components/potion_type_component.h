#ifndef POTION_TYPE_COMPONENT_H
#define POTION_TYPE_COMPONENT_H

#include <string>
#include "component.h"

class PotionTypeComponent : public Component
{
public:
    std::string potion_type;
    PotionTypeComponent(std::string potion_type);
};

#endif