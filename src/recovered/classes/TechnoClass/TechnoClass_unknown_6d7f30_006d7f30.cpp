// void TechnoClass::unknown_6d7f30() (0x006D7F30)
// Above the rules' health ratio at +0x1368 (or more than 10 below ground,
// slot 108), slot 60 of the object at +0x268.
#include "shared/techno.hpp"
// @ref ?Rules@@3PAVRulesClass@@A=00839848
// @ref ?Health_Ratio@ObjectClass@@QBENXZ=005d4540

void TechnoClass::unknown_6d7f30()
{
    if (Health_Ratio() > Rules->unknown_1368 || unknown_slot108() < -10) {
        if (unknown_25c[3] != 0) {
            unknown_25c[3]->unknown_slot60();
        }
    }
}
