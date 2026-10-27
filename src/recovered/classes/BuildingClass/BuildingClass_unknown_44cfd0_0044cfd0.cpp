// void BuildingClass::unknown_44cfd0(int index) (0x0044CFD0)
// Deletes the owned object at unknown_454[index], or all eighteen for -2.
#include "shared/building.hpp"

void BuildingClass::unknown_44cfd0(int index)
{
    if (index == -2) {
        for (int i = 0; i < 18; i++) {
            AbstractClass *object = unknown_454[i];
            if (object) {
                unknown_454[i] = 0;
                delete object;
            }
        }
    } else {
        AbstractClass *object = unknown_454[index];
        if (object) {
            unknown_454[index] = 0;
            delete object;
        }
    }
}
