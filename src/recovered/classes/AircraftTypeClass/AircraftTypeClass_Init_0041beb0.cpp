// static void AircraftTypeClass::Init() (0x0041BEB0)
// Loads the rotor shapes. Not in the function inventory (code
// 0x0041BEB0-0x0041BECE, 31 bytes, padding to 0x0041BED0).
#include "shared/aircraft_type.hpp"
#include "shared/mix_file_class.hpp"
#include "shared/cc_file_class.hpp"
// @ref ??_C@_0L@LPEL@LROTOR?4SHP?$AA@=007cea34
// @ref ?Retrieve@?$MixFileClass@VCCFileClass@@@@SIPBXPBD@Z=005956c0
// @ref ??_C@_0L@BNPA@RROTOR?4SHP?$AA@=007cea28
// @ref ?unknown_left_rotor_83c554@@3PBXB=0083c554
// @ref ?unknown_right_rotor_83c558@@3PBXB=0083c558

void AircraftTypeClass::Init()
{
    unknown_left_rotor_83c554 = MixFileClass<CCFileClass>::Retrieve("LROTOR.SHP");
    unknown_right_rotor_83c558 = MixFileClass<CCFileClass>::Retrieve("RROTOR.SHP");
}
