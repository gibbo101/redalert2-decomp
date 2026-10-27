// void HouseClass::unknown_func_4f33e0(HouseClass *house) (0x004F33E0)
// Forgets the anger at a house (adds the negated anger; name hypothesis).
#include "shared/techno.hpp"

void HouseClass::unknown_func_4f33e0(HouseClass *house)
{
    for (int index = 0; index < AngerNodes.Count(); index++) {
        if (AngerNodes[index].House == house) {
            unknown_func_4eeba0(-AngerNodes[index].Value, house);
            return;
        }
    }
}
