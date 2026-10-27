// Writes the [Infantry] section from the global infantry list (0x00506D70).
#include "shared/infantry.hpp"
#include "shared/ccini_class.hpp"
#include "shared/tag.hpp"
// @ref ?unknown_infantry_section_7a33f0@@3PBDB=007a33f0
// @ref ?Infantry@@3V?$DynamicVectorClass@PAVInfantryClass@@@@A=00a35e48
// @ref ??_C@_02MECO@?$CFd?$AA@=007ce9bc
// @ref ??_C@_04COF@None?$AA@=007ce9b4
// @ref ??_C@_0CK@MMDL@?$CFs?0?$CFs?0?$CFd?0?$CFd?0?$CFd?0?$CFd?0?$CFs?0?$CFd?0?$CFs?0?$CFd?0?$CFd@=007daf34
// @ref ?Name_From_Mission@MissionClass@@SIPBDH@Z=00595020
// @ref ?Health_Ratio@ObjectClass@@QBENXZ=005d4540
// @ref ?unknown_713580@UnknownTechnoPair@@QBEHXZ=00713580
extern char const *unknown_infantry_section_7a33f0;

void __fastcall InfantryClass::Write_INI(CCINIClass &ini)
{
    ini.Clear(unknown_infantry_section_7a33f0, 0);
    for (int index = 0; index < Infantry.Count(); index++) {
        InfantryClass *infantry = Infantry[index];
        if (!infantry->unknown_76) {
            char id[12];
            sprintf(id, "%d", index);
            char const *tag;
            if (infantry->unknown_34 != 0) {
                tag = (char const *)infantry->unknown_34->Class->ID;
            } else {
                tag = "None";
            }
            int mission = infantry->unknown_slot91() == -1 ? infantry->MissionQueue : infantry->unknown_slot91();
            unsigned raw = *(unsigned const *)&infantry->unknown_2e0.Current();
            unsigned direction = (((raw >> 7) + 1) >> 1) & 0xff;
            CoordStruct coord = infantry->Coord;
            char line[128];
            sprintf(line, "%s,%s,%d,%d,%d,%d,%s,%d,%s,%d,%d,%d,%d,%d",
                    (char const *)infantry->House->IniName, (char const *)infantry->Type->ID,
                    (int)(infantry->Health_Ratio() * 256.0),
                    infantry->unknown_slot104().X, infantry->unknown_slot104().Y,
                    Unknown_004763D0(coord),
                    MissionClass::Name_From_Mission(mission), direction, tag,
                    infantry->unknown_118.unknown_713580(), infantry->unknown_1ac,
                    infantry->unknown_79, infantry->unknown_379, infantry->unknown_37a);
            ini.Put_String(unknown_infantry_section_7a33f0, id, line);
        }
    }
}
