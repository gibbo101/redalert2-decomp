// bool AircraftTypeClass::Read_INI(CCINIClass &ini) (0x0041BFD0)
// The techno values, then the aircraft keys (rules) and the art keys
// (art INI, image section).
#include "shared/aircraft_type.hpp"
// @ref ?Read_INI@TechnoTypeClass@@UAE_NAAVCCINIClass@@@Z=006daf60
// @ref ??_C@_08GNKA@Landable?$AA@=007cea8c
// @ref ?Get_Bool@INIClass@@QBE_NPBD0_N@Z=0050f410
// @ref ??_C@_0N@JACB@AirportBound?$AA@=007cea7c
// @ref ??_C@_07IJCM@Fighter?$AA@=007cea74
// @ref ??_C@_08MALB@Carryall?$AA@=007cea68
// @ref ??_C@_06DLIC@Rotors?$AA@=007cea60
// @ref ?ArtINI@@3VCCINIClass@@A=008397f0
// @ref ??_C@_0M@NOPE@CustomRotor?$AA@=007cea54
// @ref ?unknown_string_83c55c@@3PADA=0083c55c
// @ref ??_C@_07CAOM@Trailer?$AA@=007cea4c
// @ref ?Get_String@INIClass@@QBEHPBD00PADH@Z=0050e9a0
// @ref ?Find_Or_Make@AnimTypeClass@@SIPAV1@PBD@Z=004264a0
// @ref ??_C@_0L@GPCJ@SpawnDelay?$AA@=007cea40
// @ref ?Get_Int@INIClass@@QBEHPBD0H@Z=0050d7f0

bool AircraftTypeClass::Read_INI(CCINIClass &ini)
{
    if (TechnoTypeClass::Read_INI(ini)) {
        Landable = ini.Get_Bool(ID, "Landable", Landable);
        AirportBound = ini.Get_Bool(ID, "AirportBound", AirportBound);
        Fighter = ini.Get_Bool(ID, "Fighter", Fighter);
        Carryall = ini.Get_Bool(ID, "Carryall", Carryall);
        Rotors = ArtINI.Get_Bool(unknown_1c8, "Rotors", Rotors);
        CustomRotor = ArtINI.Get_Bool(unknown_1c8, "CustomRotor", CustomRotor);
        Trailer = Get_Anim_Type(ArtINI, unknown_1c8, "Trailer", Trailer);
        SpawnDelay = ArtINI.Get_Int(unknown_1c8, "SpawnDelay", SpawnDelay);
        return true;
    }
    return false;
}
