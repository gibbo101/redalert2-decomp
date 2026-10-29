// bool __fastcall Init_Secondary_Mixfiles() -- 0x00515E70
// __fastcall (no parameters, like Init_Bootstrap_Mixfiles).
#define VECTOR_IMPLEMENT_VECTOR_ACCESSORS
#define VECTOR_IMPLEMENT_DYNAMIC_ACCESSORS
#define VECTOR_IMPLEMENT_DYNAMIC_ADD
#include "shared/vector_class.hpp"
#include "shared/cd.hpp"
#include "shared/mix_file_class.hpp"
#include "shared/cc_file_class.hpp"
#include "shared/cd_file_class.hpp"
#include "shared/raw_file_class.hpp"
#include "shared/crt_string.hpp"
#include "shared/debug_printf.hpp"
#include "shared/theme.hpp"

// @ref ?ConquerMix@@3PAV?$MixFileClass@VCCFileClass@@@@A=008374e0
// @ref ?CameoMix@@3PAV?$MixFileClass@VCCFileClass@@@@A=008374e4
// @ref ?unknown_maps_mixes_837468@@3V?$DynamicVectorClass@PAV?$MixFileClass@VCCFileClass@@@@@@A=00837468
// @ref ?unknown_movies_mixes_8374a0@@3V?$DynamicVectorClass@PAV?$MixFileClass@VCCFileClass@@@@@@A=008374a0
// @ref ?Find_Next_File@CDFileClass@@SI_NPAD@Z=00470400
// @ref ?Find_Close@CDFileClass@@SAXXZ=00470470
// @ref ?unknown_sound_enabled_a40c18@@3DA=00a40c18
// @ref ?Unknown_00496460@@YAXPBDZZ=00496460
// @ref ??_C@_0M@EIJK@CONQUER?4MIX?$AA@=007dbfd4
// @ref ??_C@_0N@PFML@?5CONQUER?4MIX?$AA@=007dbfc4
// @ref ??_C@_09BAMN@CAMEO?4MIX?$AA@=007dbfb8
// @ref ??_C@_0L@OIIE@?5CAMEO?4MIX?$AA@=007dbfac
// @ref ??_C@_09IMIE@MAPS?$CK?4MIX?$AA@=007dbfa0
// @ref ??_C@_0L@PEMO@?5MULTI?4MIX?$AA@=007dbf94
// @ref ??_C@_0L@BCGI@?5THEME?4MIX?$AA@=007dbf88
// @ref ??_C@_0BI@IOLH@u?3?2mixfiles?2MOVIES?$CK?4MIX?$AA@=007dbf70
// @ref ??_C@_0N@NGPA@MOVIES01?4MIX?$AA@=007dbf60
// @ref ??_C@_0M@FGID@MOVIES?$CK?4MIX?$AA@=007dbf54
// @ref ??_C@_0BG@BFHF@MIXFILES?2MOVIES01?4MIX?$AA@=007dbf3c
// @ref ??_C@_0BF@NDCI@MIXFILES?2MOVIES?$CK?4MIX?$AA@=007dbf24
// @ref ??_C@_0N@GFJE@MAPS?$CF02d?4MIX?$AA@=007d21d4
// @ref ??_C@_09MIH@MULTI?4MIX?$AA@=007d2180
// @ref ??_C@_09OKCB@THEME?4MIX?$AA@=007d2154
// @ref ??_C@_0P@CLBG@MOVIES?$CF02d?4MIX?$AA@=007d2144
// @ref ??_C@_03HKGO@?5?$CFs?$AA@=007dbf10

// Opens CONQUER.MIX, CAMEO.MIX, the maps (every MAPS*.MIX on a local install, else
// MAPS<disk>.MIX), MULTI.MIX and THEME.MIX, scans the themes and opens the movies the same way
// as the maps (Red Alert's Init_Secondary_Mixfiles).
bool __fastcall Init_Secondary_Mixfiles()
{
    if (CCFileClass("CONQUER.MIX").Is_Available()) {
        ConquerMix = new MixFileClass<CCFileClass>("CONQUER.MIX", &FastKey);
    }
    Unknown_00496460(" CONQUER.MIX");
    if (ConquerMix == 0) {
        return false;
    }

    if (CCFileClass("CAMEO.MIX").Is_Available()) {
        CameoMix = new MixFileClass<CCFileClass>("CAMEO.MIX", &FastKey);
    }
    Unknown_00496460(" CAMEO.MIX");
    if (CameoMix == 0) {
        return false;
    }

    int cd = Unknown_0046E4C0(60) + 1;
    char name[260];
    if (CD::IsLocal == true) {
        strcpy(name, "MAPS*.MIX");
        if (CDFileClass::Find_File(name) == true) {
            Unknown_00496460(" %s", name);
            MapsMix = new MixFileClass<CCFileClass>(name, &FastKey);
            while (CDFileClass::Find_Next_File(name) == true) {
                Unknown_00496460(" %s", name);
                MixFileClass<CCFileClass> *mix = new MixFileClass<CCFileClass>(name, &FastKey);
                if (mix != 0) {
                    MixFileClass<CCFileClass> *added = mix;
                    unknown_maps_mixes_837468.Add(added);
                }
            }
            CDFileClass::Find_Close();
        }
    } else {
        sprintf(name, "MAPS%02d.MIX", cd);
        if (CCFileClass(name).Is_Available()) {
            MapsMix = new MixFileClass<CCFileClass>(name, &FastKey);
        }
        Unknown_00496460(" %s", name);
    }
    if (MapsMix == 0) {
        return false;
    }

    if (CCFileClass("MULTI.MIX").Is_Available()) {
        MultiMix = new MixFileClass<CCFileClass>("MULTI.MIX", &FastKey);
    }
    Unknown_00496460(" MULTI.MIX");
    if (MultiMix == 0) {
        return false;
    }

    if (CCFileClass("THEME.MIX").Is_Available()) {
        ThemeMix = new MixFileClass<CCFileClass>("THEME.MIX", &FastKey);
    }
    Unknown_00496460(" THEME.MIX");
    unknown_sound_enabled_a40c18 = true;
    Theme.Scan();

    if (CD::IsLocal == true) {
        strcpy(name, "u:\\mixfiles\\MOVIES*.MIX");
        if (RawFileClass("MOVIES01.MIX").Is_Available()) {
            strcpy(name, "MOVIES*.MIX");
        }
        if (RawFileClass("MIXFILES\\MOVIES01.MIX").Is_Available()) {
            strcpy(name, "MIXFILES\\MOVIES*.MIX");
        }
        if (CDFileClass::Find_File(name) == true) {
            Unknown_00496460(" %s", name);
            MoviesMix = new MixFileClass<CCFileClass>(name, &FastKey);
            while (CDFileClass::Find_Next_File(name) == true) {
                Unknown_00496460(" %s", name);
                MixFileClass<CCFileClass> *mix = new MixFileClass<CCFileClass>(name, &FastKey);
                if (mix != 0) {
                    MixFileClass<CCFileClass> *added = mix;
                    unknown_movies_mixes_8374a0.Add(added);
                }
            }
            CDFileClass::Find_Close();
        }
    } else {
        sprintf(name, "MOVIES%02d.MIX", cd);
        if (CCFileClass(name).Is_Available()) {
            MoviesMix = new MixFileClass<CCFileClass>(name, &FastKey);
        }
        Unknown_00496460(" %s", name);
    }
    return MoviesMix ? true : false;
}
