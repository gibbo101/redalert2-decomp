// void __fastcall Read_Art_INI() (0x00652730): clears ArtINI and loads ART.INI
// into it (name hypothesis).
// __fastcall: only a fastcall caller schedules `lea ecx, file` before
// `push "ART.INI"` and `lea eax, file; mov ecx, ArtINI` before Load's pushes
// after the preceding thiscall (VC6_MATCHING_NOTES: call-argument scheduling).
// @ref ??_C@_07DCPE@ART?4INI?$AA@=007dbb58
// @ref ??_7CCFileClass@@6B@=0079a6a0
// @ref ??_7CDFileClass@@6B@=0079a658
// @ref ??_GCCFileClass@@UAEPAXI@Z=004019a0
// @ref ??_GCDFileClass@@UAEPAXI@Z=00401950
// @ref ?File_Name@RawFileClass@@UBEPBDXZ=00401940
#include "shared/ccini_class.hpp"
#include "shared/cc_file_class.hpp"

void __fastcall Read_Art_INI()
{
    ArtINI.Clear();
    CCFileClass file("ART.INI");
    ArtINI.Load(file, false, false);
}
