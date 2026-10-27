// int BuildingTypeClass::unknown_slot29() const (0x00458980)
// Pip count (RA1: Max_Pips): storage pips scale with the width.
#include "shared/building_type.hpp"
// @ref ?Rules@@3PAVRulesClass@@A=00839848
// @ref ?unknown_foundation_width_7cfc70@@3QBHB=007cfc70
// @ref ?unknown_slot29@TechnoTypeClass@@UBEHXZ=006de220

int BuildingTypeClass::unknown_slot29() const
{
    int max = Width() * 60 / 8;
    switch (PipScale) {
    case 2:
        if (Weeder) {
            int storage = Rules->unknown_1410;
            if (storage < 0) {
                return 0;
            }
            return storage > max ? max : storage;
        } else {
            int storage = Storage;
            if (storage < 0) {
                return 0;
            }
            return storage > max ? max : storage;
        }
    case 4:
        return max;
    }
    return TechnoTypeClass::unknown_slot29();
}
