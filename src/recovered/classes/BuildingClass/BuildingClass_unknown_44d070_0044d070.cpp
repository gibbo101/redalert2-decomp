// Change attached animation damage state and restart each occupied slot.
#include "shared/building.hpp"
void BuildingClass::unknown_44d070(bool damaged)
{
    if (unknown_5b6 == damaged) return;
    unknown_5b6 = damaged;
    for (int index = 0; index < 18; ++index) {
        if (unknown_454[index]) unknown_44c920(index, damaged, false, 0);
    }
}
