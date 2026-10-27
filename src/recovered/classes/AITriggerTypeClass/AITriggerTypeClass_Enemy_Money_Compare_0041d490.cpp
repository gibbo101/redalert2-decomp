// bool AITriggerTypeClass::Enemy_Money_Compare(HouseClass *house, HouseClass *enemy) const (0x0041D490)
// Compares the enemy's available money with the comparator's value using its
// operator (0 <, 1 <=, 2 ==, 3 >=, 4 >, 5 !=).
#include "shared/ai_trigger_type.hpp"
#include "shared/house.hpp"

bool AITriggerTypeClass::Enemy_Money_Compare(HouseClass *house, HouseClass *enemy) const
{
    bool result = false;
    if (enemy != 0) {
        IHouse *ihouse = enemy;
        long money = ihouse->Available_Money();
        switch (((int const *)Comparator)[1]) {
        case 0:
            result = money < ((int const *)Comparator)[0];
            break;
        case 1:
            result = money <= ((int const *)Comparator)[0];
            break;
        case 2:
            result = money == ((int const *)Comparator)[0];
            break;
        case 3:
            result = money >= ((int const *)Comparator)[0];
            break;
        case 4:
            result = money > ((int const *)Comparator)[0];
            break;
        case 5:
            result = money != ((int const *)Comparator)[0];
            break;
        }
    }
    return result;
}
