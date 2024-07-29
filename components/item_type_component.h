#include <string>

#include "component.h"

class ItemTypeComponent : public Component
{
public:
    std::string item_type;
    ItemTypeComponent(std::string item_type);
};