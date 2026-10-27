// int __fastcall Coop_Camp_Unique_ID() (0x00652520, 196 bytes: 0x652520-0x6525E3,
// ret at 0x6525E3; the inventory splits it mid-instruction into 0x652520/0x652570).
// The CRC identifier (CCINIClass::Get_Unique_ID) of CoopCamp.ini, read once and
// kept; 0x006525F0 adds it to the rules/session INI identifiers.
// __fastcall: the Rules unit's free functions with parameters are fastcall (Get_Type,
// Difficulty_Get); with no parameters the call sites cannot tell, but only a fastcall
// caller schedules `lea ecx, file` before `push "CoopCamp.ini"` after the GenericList
// constructor call (VC6_MATCHING_NOTES: call-argument scheduling).
// The two globals follow the unit's geometry statics in .bss (0x00AB6D78-0x00AB6DE8);
// names are hypotheses.
// @ref ??_C@_0N@OG@CoopCamp?4ini?$AA@=007d514c
// @ref ?CoopCampLoaded@@3_NA=00ab6df0
// @ref ?CoopCampUniqueID@@3HA=00ab6dec
// @ref ??_7?$List@PAUINISection@INIClass@@@@6B@=0079aaec
// @ref ??_7CCINIClass@@6B@=0079aae4
// @ref ??_7CCFileClass@@6B@=0079a6a0
// @ref ??_7CDFileClass@@6B@=0079a658
// @ref ??_GCCINIClass@@UAEPAXI@Z=0040e2e0
// @ref ??_G?$List@PAUINISection@INIClass@@@@UAEPAXI@Z=0040e300
// @ref ??_GGenericList@@UAEPAXI@Z=0040e220
// @ref ??_GGenericNode@@UAEPAXI@Z=0040e1d0
// @ref ??_GCCFileClass@@UAEPAXI@Z=004019a0
// @ref ??_GCDFileClass@@UAEPAXI@Z=00401950
// @ref ?File_Name@RawFileClass@@UBEPBDXZ=00401940
#include "shared/ccini_class.hpp"
#include "shared/cc_file_class.hpp"

extern bool CoopCampLoaded;         // 0x00AB6DF0
extern int CoopCampUniqueID;        // 0x00AB6DEC

int __fastcall Coop_Camp_Unique_ID()
{
    if (!CoopCampLoaded) {
        CCINIClass ini;
        CCFileClass file("CoopCamp.ini");
        if (ini.Load(file, false, false)) {
            CoopCampUniqueID = ini.Get_Unique_ID();
        }
        CoopCampLoaded = true;
    }
    return CoopCampUniqueID;
}
