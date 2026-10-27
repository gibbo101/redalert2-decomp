// bool AITriggerTypeClass::House_Owns_Compare(HouseClass *house, HouseClass *enemy) const (0x0041D0F0)
// Compares how many objects of the condition type the house itself owns
// with the comparator (Owned_Count is defined with 0x0041CD50 in this unit).
#include "shared/ai_trigger_type.hpp"
#include "shared/house.hpp"

bool AITriggerTypeClass::House_Owns_Compare(HouseClass *house, HouseClass *enemy) const
{
    bool result = false;
    if (house != 0) {
        int count = Owned_Count(house);
        switch (((int const *)Comparator)[1]) {
        case 0:
            result = count < ((int const *)Comparator)[0];
            break;
        case 1:
            result = count <= ((int const *)Comparator)[0];
            break;
        case 2:
            result = count == ((int const *)Comparator)[0];
            break;
        case 3:
            result = count >= ((int const *)Comparator)[0];
            break;
        case 4:
            result = count > ((int const *)Comparator)[0];
            break;
        case 5:
            result = count != ((int const *)Comparator)[0];
            break;
        }
    }
    return result;
}
