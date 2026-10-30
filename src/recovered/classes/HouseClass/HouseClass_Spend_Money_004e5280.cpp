// House money spending, 0x004E5280; 436-byte body, 12-byte tail.
#include "shared/techno.hpp"
#include "shared/tiberium.hpp"
// @ref ?Get_Amount@StorageClass@@QBEMH@Z=0069ae40

void HouseClass::Spend_Money_004e5280(int money)
{
    float old_amount = Tiberium.Get_Total_Amount();
    int old_capacity = Capacity;
    int spent;
    int remaining = money;
    if (money > Balance) {
        remaining -= Balance;
        spent = Balance;
        Balance = 0;
    } else {
        Balance -= money;
        spent = money;
        remaining = 0;
    }
    if (remaining > 0 && Tiberium.Get_Total_Amount() > 0.0f) {
        int count = Buildings.Count();
        for (int index = 0; index < count; ++index) {
            TechnoClass *building = (TechnoClass *)Buildings[index];
            if (building) {
                StorageClass &storage = building->unknown_294;
                while (storage.Get_Total_Amount() > 0.0f && remaining > 0) {
                    int type = storage.First_Used_Slot();
                    while (remaining > 0 && storage.Get_Amount(type) > 0.0f) {
                        float removed = storage.Remove_Amount(1.0f, type);
                        Tiberium.Remove_Amount(removed, type);
                        int value = (int)(unknown_TiberiumClass_list_00ac0b30[type]->Value *
                            Type->unknown_0x148 * removed);
                        remaining -= value;
                        spent += value;
                        if (remaining < 0) {
                            Balance -= remaining;
                            spent += remaining;
                            remaining = 0;
                            break;
                        }
                        if (remaining <= 0) break;
                    }
                }
            }
            if (!remaining) break;
        }
    }
    Silo_Redraw_Check((int)old_amount, old_capacity);
    unknown_21c += spent;
}
