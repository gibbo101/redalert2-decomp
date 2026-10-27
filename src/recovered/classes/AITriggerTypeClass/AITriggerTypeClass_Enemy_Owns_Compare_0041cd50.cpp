// bool AITriggerTypeClass::Enemy_Owns_Compare(HouseClass *house, HouseClass *enemy) const (0x0041CD50)
// Compares how many objects of the condition type (unknown_d8) the enemy owns
// with the comparator's value using its operator (0 <, 1 <=, 2 ==, 3 >=,
// 4 >, 5 !=). The count comes from the enemy's per-kind counters: building
// (kind 7), unit (0x28), infantry (0x10) and aircraft (3) types.
#include "shared/ai_trigger_type.hpp"
#include "shared/house.hpp"
// @ref ?unknown_func_491d10@UnknownHouseCounter@@QAEHH@Z=00491d10

// How many objects of the condition type the house owns (its per-kind counters).
inline int AITriggerTypeClass::Owned_Count(HouseClass *house) const
{
    AbstractTypeClass *type = unknown_d8;
    if (type != 0) {
        int index = type->unknown_slot16();
        int count = 0;
        switch (type->Kind_Of()) {
        case 7:
            count = house->unknown_5460.unknown_func_491d10(index);
            break;
        case 0x28:
            count = house->unknown_5470.unknown_func_491d10(index);
            break;
        case 0x10:
            count = house->unknown_5480.unknown_func_491d10(index);
            break;
        case 3:
            count = house->unknown_5490.unknown_func_491d10(index);
            break;
        }
        return count;
    }
    return 0;
}

bool AITriggerTypeClass::Enemy_Owns_Compare(HouseClass *house, HouseClass *enemy) const
{
    bool result = false;
    if (enemy != 0) {
        int count = Owned_Count(enemy);
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
