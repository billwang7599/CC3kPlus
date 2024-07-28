
class Component;

class DisplayComponent : public Component
{
public:
    const char display_char;
    DisplayComponent(const std::string &name, char display) : display_char{display} {};
};
