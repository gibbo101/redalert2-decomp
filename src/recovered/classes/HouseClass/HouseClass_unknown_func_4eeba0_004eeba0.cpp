// void HouseClass::unknown_func_4eeba0(int amount, HouseClass *house) (0x004EEBA0)
// Adds to the anger at a house, then picks the house it is angriest at
// among the remaining non-allied houses (+0x54F0: its index, -1 for none).
#include "shared/techno.hpp"

void HouseClass::unknown_func_4eeba0(int amount, HouseClass *house)
{
    for (int index = 0; index < AngerNodes.Count(); index++) {
        if (AngerNodes[index].House == house) {
            AngerNodes[index].Value += amount;
        }
    }
    int best = 0;
    HouseClass *angriest = 0;
    for (index = 0; index < AngerNodes.Count(); index++) {
        int value = AngerNodes[index].Value;
        HouseClass *other = AngerNodes[index].House;
        if (value > best && !other->unknown_13d && !Is_Ally(other)) {
            best = value;
            angriest = other;
        }
    }
    if (angriest != 0) {
        unknown_54f0 = angriest->ArrayIndex;
    } else {
        unknown_54f0 = -1;
    }
}
