// WDTTerritory (moved out of shared/world_domination_tour.hpp so a unit can use a territory
// without that header's function statics).
#ifndef RA2_SHARED_WDT_TERRITORY_HPP
#define RA2_SHARED_WDT_TERRITORY_HPP
#include "shared/reference_counted.hpp"

// WDTTerritory (RTTI vtable 0x007AF2D8, global namespace; size 0x40): one
// territory of the WDTState, made by the rc_ptr<WDTTerritory> factory
// 0x0072BDC0 (constructor 0x0072BE00). Only the fields the recovered units
// read; the game options (Conflict.cpp, WDTGameOptions.cpp) read the battle
// settings from it.
class WDTTerritory : public ReferenceCounted {
public:
    WDTTerritory();                                 // 0x0072BE00 (the default settings)
    static rc_ptr<WDTTerritory> __fastcall Create();   // 0x0072BDC0

    int unknown_08;                                 // +0x08 (Conflict 0x007273F0)
    char unknown_0c[0x0E - 0x0C];
    unsigned char UnitCount;                        // +0x0E (WDT:UnitCount)
    unsigned char TechLevel;                        // +0x0F (WDT:TechLevel)
    unsigned short unknown_10;                      // +0x10 (the session's +0x24, unknown_session_a3d2bc)
    unsigned char unknown_12;                       // +0x12 (MapSizeGameOption)
    unsigned char unknown_13;                       // +0x13 (MapSizeGameOption)
    unsigned char PlayerCount;                      // +0x14 (4: WDT:FourPlayerOnly)
    char unknown_15[0x38 - 0x15];
    int OptionFlags;                                // +0x38 FlagGameOption bits
    int unknown_3c;                                 // +0x3C
};

#endif
