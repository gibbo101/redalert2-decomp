// void HouseClass::Refund_Money(int amount) (0x004E5440)
#include "shared/techno.hpp"

void HouseClass::Refund_Money(int amount)
{
    Balance += amount;
}
