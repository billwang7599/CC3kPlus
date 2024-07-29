#ifndef ITEM_TYPE_COMPONENT_H
#define ITEM_TYPE_COMPONENT_H

#include <string>
#include "component.h"

class ItemTypeComponent : public Component
{
public:
    std::string item_type;
    ItemTypeComponent(std::string item_type) : item_type{item_type} {}
};

#endif