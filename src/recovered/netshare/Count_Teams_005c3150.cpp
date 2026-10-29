// int __fastcall Count_Teams_005c3150(HouseClass *exclude) (0x005C3150)
// Counts the teams among the live houses that have unknown_134 set (exclude left out): a house allied both
// ways with another counts once for the group, at its first allied partner after it; a house without such a
// partner counts alone.
#include "shared/lobby.hpp"
#include "shared/house.hpp"

int __fastcall Count_Teams_005c3150(HouseClass *exclude)
{
    int count = 0;
    for (int i = 0; i < Houses.Count(); i++) {
        HouseClass *house = Houses[i];
        if (house != 0 && !house->unknown_13d && house->unknown_134 && house != exclude) {
            bool allied = false;
            for (int j = 0; j < Houses.Count(); j++) {
                if (j != i) {
                    HouseClass *other = Houses[j];
                    if (other != 0 && !other->unknown_13d && other->unknown_134 && other != exclude
                        && house->Is_Ally(other) && other->Is_Ally(house)) {
                        if (j > i && !allied) {
                            count++;
                        }
                        allied = true;
                    }
                }
            }
            if (!allied) {
                count++;
            }
        }
    }
    return count;
}
