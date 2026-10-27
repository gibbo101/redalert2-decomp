// @ref ??_C@_0CE@FLLK@?$CFs?0?$CFs?0?$CFd?0?$CFd?0?$CFd?0?$CFd?0?$CFs?0?$CFs?0?$CFd?0?$CFd?0?$CFd@=007ce990
// Aircraft.cpp INI output at0041A6C0; static member spelling is a source identity hypothesis.
#include "shared/aircraft.hpp"
#include "shared/ccini_class.hpp"
#include "shared/house.hpp"
// @ref ?unknown_aircraft_section_79b0d0@@3PBDB=0079b0d0
// @ref ??_C@_02MECO@?$CFd?$AA@=007ce9bc
// @ref ??_C@_04COF@None?$AA@=007ce9b4
// @ref ?Name_From_Mission@MissionClass@@SIPBDH@Z=00595020
// @ref ?Health_Ratio@ObjectClass@@QBENXZ=005d4540
// @ref ?unknown_713580@UnknownTechnoPair@@QBEHXZ=00713580
extern char const *unknown_aircraft_section_79b0d0;
void __fastcall AircraftClass::Write_INI_0041A6C0(CCINIClass &ini)
{
    ini.Clear(unknown_aircraft_section_79b0d0, 0);
    for (int index = 0; index < Aircraft.Count(); index++) {
        AircraftClass *aircraft = Aircraft[index];
        if (aircraft && !aircraft->unknown_76 && aircraft->unknown_7d) {
            char id[12];
            sprintf(id, "%d", index);
            char const *tag;
            if (aircraft->unknown_34) tag = (char const *)aircraft->unknown_34->Class->ID;
            else tag = "None";
            unsigned raw = *(unsigned const *)&aircraft->unknown_2e0.Current();
            unsigned direction = (((raw >> 7) + 1) >> 1) & 0xff;
            char line[128];
            sprintf(line, "%s,%s,%d,%d,%d,%d,%s,%s,%d,%d,%d,%d",
                    (char const *)aircraft->House->IniName, (char const *)aircraft->Type->ID,
                    (int)(aircraft->Health_Ratio() * 256.0),
                    aircraft->unknown_slot104().X, aircraft->unknown_slot104().Y,
                    direction, MissionClass::Name_From_Mission(aircraft->unknown_slot91()), tag,
                    aircraft->unknown_118.unknown_713580(), aircraft->unknown_1ac,
                    aircraft->unknown_379, aircraft->unknown_37a);
            ini.Put_String(unknown_aircraft_section_79b0d0, id, line);
        }
    }
}
