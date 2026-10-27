// static void __fastcall UnitClass::Write_INI(CCINIClass &ini) (0x00706F60)
// Writes the [Units] section: it clears the section, then adds one line per active unit that is on
// the map (hypothesis; the inverse of Read_INI): house, type, strength (0-256), cell x and y,
// facing (0-255), mission, attached tag name ("None" without), the +0x118 value, +0x1AC, +0x79,
// the index of the linked unit (-1 without), +0x379 and +0x37A.
#include "shared/unit.hpp"
#include "shared/ccini_class.hpp"
#include "shared/mission.hpp"
#include "shared/tag.hpp"
// @ref ?Units@@3V?$DynamicVectorClass@PAVUnitClass@@@@A=00866198
// @ref ?unknown_units_section_7addc0@@3PBDB=007addc0
// @ref ??_C@_02MECO@?$CFd?$AA@=007ce9bc
// @ref ??_C@_04COF@None?$AA@=007ce9b4
// @ref ??_C@_0CK@COGK@?$CFs?0?$CFs?0?$CFd?0?$CFd?0?$CFd?0?$CFd?0?$CFs?0?$CFs?0?$CFd?0?$CFd?0?$CFd@=007f8f8c
// @ref ?Name_From_Mission@MissionClass@@SIPBDH@Z=00595020
// @ref ?Health_Ratio@ObjectClass@@QBENXZ=005d4540
// @ref ?unknown_713580@UnknownTechnoPair@@QBEHXZ=00713580

extern char const *unknown_units_section_7addc0;

void __fastcall UnitClass::Write_INI(CCINIClass &ini)
{
    ini.Clear(unknown_units_section_7addc0, 0);
    for (int index = 0; index < Units.Count(); index++) {
        UnitClass *unit = Units[index];
        if (unit != 0 && !unit->unknown_76 && unit->unknown_7d) {
            char id[12];
            sprintf(id, "%d", index);
            int linked = unit->unknown_5b0 != 0 ? Units.ID((UnitClass *)unit->unknown_5b0) : -1;
            char const *tag;
            if (unit->unknown_34 != 0 && unit->unknown_34->Class != 0) {
                tag = (char const *)unit->unknown_34->Class->ID;
            } else {
                tag = "None";
            }
            unsigned raw = *(unsigned const *)&unit->unknown_2e0.Current();
            unsigned direction = (((raw >> 7) + 1) >> 1) & 0xff;
            char line[128];
            sprintf(line, "%s,%s,%d,%d,%d,%d,%s,%s,%d,%d,%d,%d,%d,%d",
                    (char const *)unit->House->IniName, (char const *)unit->Type->ID,
                    (int)(unit->Health_Ratio() * 256.0),
                    unit->unknown_slot104().X, unit->unknown_slot104().Y,
                    direction,
                    MissionClass::Name_From_Mission(unit->unknown_slot91()), tag,
                    unit->unknown_118.unknown_713580(), unit->unknown_1ac, unit->unknown_79, linked,
                    unit->unknown_379, unit->unknown_37a);
            ini.Put_String(unknown_units_section_7addc0, id, line);
        }
    }
}
