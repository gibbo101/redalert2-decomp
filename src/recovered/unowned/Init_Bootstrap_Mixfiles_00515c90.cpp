// bool __fastcall Init_Bootstrap_Mixfiles() -- 0x00515C90
// __fastcall (no parameters): as __cdecl VC6 schedules the object address loads after the argument pushes.
// Body 0x00515C90-0x00515E6B (476 bytes; the inventory start 0x00515D00 is inside it).
#define VECTOR_IMPLEMENT_DYNAMIC_ADD
#include "shared/vector_class.hpp"
#include "shared/cd.hpp"
#include "shared/mix_file_class.hpp"
#include "shared/raw_file_class.hpp"
#include "shared/crt_string.hpp"
#include "shared/debug_printf.hpp"

// @ref ?unknown_ra2_mix_8374b8@@3PAVMixFileClass@@A=008374b8
// @ref ?unknown_cache_mix_8374e8@@3PAVMixFileClass@@A=008374e8
// @ref ?unknown_local_mix_8374ec@@3PAVMixFileClass@@A=008374ec
// @ref ?Unknown_00496460@@YAXPBDZZ=00496460
// @ref ??_C@_0P@DEGN@EXPAND?$CF02d?4MIX?$AA@=007dbf14
// @ref ??_C@_03HKGO@?5?$CFs?$AA@=007dbf10
// @ref ??_C@_07KLDL@RA2?4MIX?$AA@=007dbf08
// @ref ??_C@_0L@FEBF@?5CACHE?4MIX?$AA@=007dbefc
// @ref ??_C@_09KMFM@CACHE?4MIX?$AA@=007dbef0
// @ref ??_C@_09JJNI@LOCAL?4MIX?$AA@=007dbee4
// @ref ??_C@_0L@GBJB@?5LOCAL?4MIX?$AA@=007dbed8

// Opens the EXPAND99.MIX..EXPAND00.MIX found on disk, then RA2.MIX, CACHE.MIX (cached) and
// LOCAL.MIX, with any disk allowed meanwhile (Red Alert's Init_Bootstrap_Mixfiles).
bool __fastcall Init_Bootstrap_Mixfiles()
{
    int cd = CD::RequiredCD;
    CD::Set_Required_CD(-2);
    for (int index = 99; index >= 0; index--) {
        char name[64];
        sprintf(name, "EXPAND%02d.MIX", index);
        if (RawFileClass(name).Is_Available()) {
            MixFileClass *mix = new MixFileClass(name, &FastKey);
            if (mix != 0) {
                unknown_expansion_mixes_837450.Add(mix);
                Unknown_00496460(" %s", name);
            }
        }
    }

    unknown_ra2_mix_8374b8 = new MixFileClass("RA2.MIX", &FastKey);
    if (unknown_ra2_mix_8374b8 == 0) {
        return false;
    }
    Unknown_00496460(" CACHE.MIX");

    unknown_cache_mix_8374e8 = new MixFileClass("CACHE.MIX", &FastKey);
    if (unknown_cache_mix_8374e8 == 0 || !MixFileClass::Cache("CACHE.MIX")) {
        return false;
    }
    Unknown_00496460(" CACHE.MIX");

    unknown_local_mix_8374ec = new MixFileClass("LOCAL.MIX", &FastKey);
    if (unknown_local_mix_8374ec == 0) {
        return false;
    }
    Unknown_00496460(" LOCAL.MIX");
    CD::Set_Required_CD(cd);
    return true;
}
