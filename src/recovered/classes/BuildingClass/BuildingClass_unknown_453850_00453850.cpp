// void BuildingClass::unknown_453850() (0x00453850)
// Restarts the timer at +0x5A0 with the type's ProduceCashDelay; then, for
// a house that is not MultiplayPassive and when slot 195 holds, pays the
// type's ProduceCashAmount into the house (a negative amount is spent).
#include "shared/building.hpp"
#include "shared/house.hpp"
// @ref ?Refund_Money@HouseClass@@QAEXH@Z=004e5440
// @ref ?Unknown_004E5280@HouseClass@@QAEXH@Z=004e5280

void BuildingClass::unknown_453850()
{
    unknown_5a0 = CDTimerClass<FrameTimerClass>(Type->ProduceCashDelay);
    if (!House->Type->MultiplayPassive && unknown_slot195()) {
        int amount = Type->ProduceCashAmount;
        if (amount > 0) {
            House->Refund_Money(amount);
        } else {
            House->Unknown_004E5280(-amount);
        }
    }
}
