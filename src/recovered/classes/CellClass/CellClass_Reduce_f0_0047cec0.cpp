// void CellClass::Reduce_f0(double amount) (0x0047CEC0): subtracts amount
// from +0xF0, clamping at zero.
#include "shared/cell.hpp"

void CellClass::Reduce_f0(double amount)
{
    double value = (unknown_f0 -= amount);
    unknown_f0 = 0.0 > value ? 0.0 : value;
}
