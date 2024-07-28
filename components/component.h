#include <string>

class Component
{
public:
    virtual ~Component() = default;
    std::string get_name() const { return name; }
};