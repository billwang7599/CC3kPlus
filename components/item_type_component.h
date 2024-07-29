#include "component.h"
#include <string>

class ItemTypeComponent : public Component
{
public:
    std::string item_type;
    ItemTypeComponent(std::string item_type) : item_type{item_type} {};
};
