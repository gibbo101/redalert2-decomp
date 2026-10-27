// bool TechnoClass::unknown_slot245(HouseClass *house) (0x006D8CE0, slot 245)
// Whether house cannot see the techno right now: while the +0x184 timer
// runs for an owner failing HouseClass 0x004F52B0; for owners passing it,
// slot 48 holders outside the visible part of the pulse; otherwise slot 48
// holders on a cell 0x0047C300 refuses for house are visible (false).
#include "shared/techno.hpp"
// @ref ?Frame@@3HA=00a40d2c
// @ref ?Unknown_004F52B0@HouseClass@@QAE_NXZ=004f52b0
// @ref ?unknown_47c300@UnknownCellClass@@QAE_NH@Z=0047c300

bool TechnoClass::unknown_slot245(HouseClass *house)
{
    if (unknown_184.Value() != 0 && !House->Unknown_004F52B0()) {
        return true;
    }
    if (House->Unknown_004F52B0() && unknown_slot48()) {
        int phase = (Frame - unknown_174 + 64) % 256;
        if (phase >= 72 && phase <= 119) {
            return false;
        }
        return true;
    }
    UnknownCellClass *cell = (UnknownCellClass *)unknown_slot105();
    if (unknown_slot48() && cell != 0 && !cell->unknown_47c300(house->ArrayIndex)) {
        return false;
    }
    return true;
}
