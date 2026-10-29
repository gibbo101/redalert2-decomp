// bool Init_Expansion_Files() -- 0x00515AF0
// Opens every ECACHE*.MIX (cached) and ELOCAL*.MIX found in the game folder
// with the fast key and lists them (as Red Alert's Init_Expansion_Files with
// SC*.MIX and SS*.MIX). Body 0x00515AF0-0x00515C85 (406 bytes): the inventory
// start 0x00515B40 is inside it (mid-instruction; no reference).
#define VECTOR_IMPLEMENT_DYNAMIC_ADD
#include "shared/vector_class.hpp"
#include "shared/win32_find.hpp"
#include "shared/cd.hpp"
#include "shared/mix_file_class.hpp"
// @ref ??0?$MixFileClass@VCCFileClass@@@@QAE@PBDPBVPKey@@@Z=005952f0
// @ref ?Cache@?$MixFileClass@VCCFileClass@@@@QAE_NPBVBuffer@@@Z=00595810
// @ref ?FastKey@@3VPKey@@A=00839010
// @ref ?unknown_expansion_mixes_837450@@3V?$DynamicVectorClass@PAV?$MixFileClass@VCCFileClass@@@@@@A=00837450
// @ref ??_C@_0M@DOBJ@ECACHE?$CK?4MIX?$AA@=007dbecc
// @ref ??_C@_0M@BCCM@ELOCAL?$CK?4MIX?$AA@=007dbec0

bool __cdecl Init_Expansion_Files()
{
    WIN32_FIND_DATA data;
    HANDLE handle = FindFirstFileA("ECACHE*.MIX", &data);
    if (handle != INVALID_HANDLE_VALUE) {
        do {
            if ((data.dwFileAttributes & 0x116) == 0) {
                MixFileClass<CCFileClass> *mix = new MixFileClass<CCFileClass>(data.cFileName, &FastKey);
                if (mix != 0) {
                    unknown_expansion_mixes_837450.Add(mix);
                    mix->Cache();
                }
            }
        } while (FindNextFileA(handle, &data));
        FindClose(handle);
    }
    handle = FindFirstFileA("ELOCAL*.MIX", &data);
    if (handle != INVALID_HANDLE_VALUE) {
        do {
            if ((data.dwFileAttributes & 0x116) == 0) {
                MixFileClass<CCFileClass> *mix = new MixFileClass<CCFileClass>(data.cFileName, &FastKey);
                if (mix != 0) {
                    unknown_expansion_mixes_837450.Add(mix);
                }
            }
        } while (FindNextFileA(handle, &data));
        FindClose(handle);
    }
    return true;
}
