#include "component.h"

class PositionComponent : public Component
{
public:
    int row, col;
    PositionComponent(int row, int col);
};