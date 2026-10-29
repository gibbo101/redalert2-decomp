// int __fastcall Unregister_Com_Server() (0x0068E040)
// Deletes the keys Register_Com_Server writes: the two ProgIDs (subkeys
// first), the class key's subkeys and the class key itself.
#include "shared/com_registration.hpp"
#include "shared/win32_api.hpp"
// @ref ??_C@_06HFAC@CLSID?2?$AA@=007f4dc8
// @ref ??_C@_0BG@HCLN@WW?4TiberianSun?2CurVer?$AA@=007f4e08
// @ref ??_C@_0BF@GFPO@WW?4TiberianSun?2CLSID?$AA@=007f4df0
// @ref ??_C@_0P@ICEP@WW?4TiberianSun?$AA@=007f4d8c
// @ref ??_C@_0BH@CMHC@WW?4TiberianSun?41?2CLSID?$AA@=007f4dd8
// @ref ??_C@_0BB@PJMD@WW?4TiberianSun?41?$AA@=007f4db4
// @ref ??_C@_05KEJO@?$CFs?2?$CFs?$AA@=007f4dd0
// @ref ??_C@_06CMNK@ProgID?$AA@=007f4d7c
// @ref ??_C@_0BJ@LMLI@VersionIndependentProgID?$AA@=007f4d60
// @ref ??_C@_0O@GBJK@NotInsertable?$AA@=007f4d50
// @ref ??_C@_0P@IIOA@InprocServer32?$AA@=007f4d40
// @ref ??_C@_07GICL@Typelib?$AA@=007f4d38
// @ref _CLSID_TiberianSun=007a1a90
// @ref __imp__StringFromGUID2@12=0079a5d4

int __fastcall Unregister_Com_Server()
{
    char path[300];
    wchar_t wide[40];
    char clsid_string[40];
    char class_key[72];

    StringFromGUID2(CLSID_TiberianSun, wide, 39);
    WideCharToMultiByte(0, 0x20, wide, -1, clsid_string, 39, 0, 0);
    lstrcpyA(class_key, "CLSID\\");
    lstrcatA(class_key, clsid_string);

    RegDeleteKeyA(HKEY_CLASSES_ROOT, "WW.TiberianSun\\CurVer");
    RegDeleteKeyA(HKEY_CLASSES_ROOT, "WW.TiberianSun\\CLSID");
    RegDeleteKeyA(HKEY_CLASSES_ROOT, "WW.TiberianSun");
    RegDeleteKeyA(HKEY_CLASSES_ROOT, "WW.TiberianSun.1\\CLSID");
    RegDeleteKeyA(HKEY_CLASSES_ROOT, "WW.TiberianSun.1");
    wsprintfA(path, "%s\\%s", class_key, "ProgID");
    RegDeleteKeyA(HKEY_CLASSES_ROOT, path);
    wsprintfA(path, "%s\\%s", class_key, "VersionIndependentProgID");
    RegDeleteKeyA(HKEY_CLASSES_ROOT, path);
    wsprintfA(path, "%s\\%s", class_key, "NotInsertable");
    RegDeleteKeyA(HKEY_CLASSES_ROOT, path);
    wsprintfA(path, "%s\\%s", class_key, "InprocServer32");
    RegDeleteKeyA(HKEY_CLASSES_ROOT, path);
    wsprintfA(path, "%s\\%s", class_key, "Typelib");
    RegDeleteKeyA(HKEY_CLASSES_ROOT, path);
    RegDeleteKeyA(HKEY_CLASSES_ROOT, class_key);
    return 0;
}
