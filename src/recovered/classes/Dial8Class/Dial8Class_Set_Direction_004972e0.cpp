#include "shared/dial8.hpp"
void Dial8Class::Set_Direction(unsigned direction)
{
    Update_Direction(direction);
    Previous = Selected;
    Flag_To_Redraw();
}
